//
// Created by kiosk on 19-10-1.
//

#ifndef MY_REDIES_SSTABLE_H
#define MY_REDIES_SSTABLE_H

#include <vector>
#include <string>
#include <snappy.h>
#include <algorithm>
#include <atomic>
#include <memory>
#include "../base/options.h"
#include "../base/sds.h"
#include "../util/bloom_filter.h"
#include "../base/options.h"
#include "../base/decondig.h"
using namespace deconding;
//
//fifter
//block
//总目录
//静态索引一层，数据一层
class bloom;
class options;
class sstable{
public:
    sstable() :idea_(0),number_(0),
    option_(std::make_unique<options>()),
    file_size(0){

    };
    ~sstable() = default;
    void add(std::string & key,sds &value)
    {
        if(idea_.load(std::memory_order_relaxed) == 16)
        {
            restarte_.emplace_back(key,recode_.size());
            idea_.store(0,std::memory_order_relaxed);
        }else{
            snappy::Compress(key.data(),key.size(),&key);
        }
        recode_.emplace_back(key,value); //  进行插入
        idea_.store(idea_.load(std::memory_order_relaxed) + 1,std::memory_order_relaxed);
    }
    void bloomadd(std::unique_ptr<bloom> &&bl){
        bloom_.emplace_back(std::move(bl));
    }
    void save(){
            std::string name("."+std::to_string(number_) + "tts");
    }
    void write_file(std::string &name);
    void append(std::string & buffer);
private:
    struct fifter{
        uint32_t  begin;
        uint32_t  offest; //每一块过滤的起始位置和偏移量
    };
    std::vector<fifter> fifter_ ; //布隆过滤器的总目录
    struct index{
       sds key_; // 每一块最后的key
       char  *offest_; // 每一个数据块的偏移位置
       index(std::string & key,uint32_t offest) : key_(key){
           char data[5];
           bzero(data, sizeof(data));
           EncodeInt32(data,offest);
           offest_ = new char[strlen(data)];
           strcpy(offest_,data);
       }
       ~index(){
           delete [] offest_;
       }
    };
    std::vector<index> index_;//生成一块静态索引
    std::vector<index> restarte_; // 重启点
    //重启点
    struct recode{
    private:
         uint32_t key_length;
         std::string key;
         uint32_t value_length;
         sds value;
    public:
         bool operator < (recode & rhs){
             return this->key < rhs.key;
         }
         recode(std::string & key_ , sds &value_) : key_length(key_.size()),
         key(key_),value_length(value_.size()),value(value_){
         }
         ~recode() = default;
         std::string key_(){
             return key;
         }
         std::string value_(){
             return value.Tostring();
         }

    };
    std::vector<recode> recode_; //数据块
    //总的过滤器 延长生命周期
    std::vector<std::unique_ptr<bloom>> bloom_;
    std::atomic_int idea_;// 对于重启点进行记录
    //必须限制sstable的个数多少
    std::atomic_int number_; // sstable的个数目前设置为4第一层
    std::unique_ptr<options> option_; // 对于选项参数设置
    unsigned long  long file_size ; // 目前已经存储块的长度
};

#endif //MY_REDIES_SSTABLE_H
