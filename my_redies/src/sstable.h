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
#include "../base/decondig.cc"
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
    void add(std::basic_string<char> key, sds &value)
    {
        if(idea_.load(std::memory_order_relaxed) == 16)
        {
            restarte_.emplace_back(key,recode_.size() + file_size);
            idea_.store(0,std::memory_order_relaxed);
        }else{
            snappy::Compress(key.data(),key.size(),&key);
        }
        recode_.emplace_back(key,value); //  进行插入
        idea_.store(idea_.load(std::memory_order_relaxed) + 1,std::memory_order_relaxed);
    }
    void bloomadd(std::shared_ptr<bloom> &bl){
        bloom_.emplace_back(std::move(bl));
    }
    void save(){

        if(file_size <= option_->write_()) { // 完全的
            append(buffer_);
            indexblock_.emplace_back(file_size,buffer_.size() + file_size);
            std::string name("." + std::to_string(number_) + "tts");
            write_file(name, buffer_);
        }
    }
    void write_file(std::string &name,std::string &buffer);
    void append(std::string & buffer);
    void write_fifter(std::string & name, std::string *buffer){
        for(auto &c : bloom_)
        {
            fifter_.emplace_back(file_size,file_size + 1024);
            c->write_(name,&file_size);
            //每次一个加1024
        }
        append_(indexblock_,buffer);
        if(buffer->size() <= 64)
        {
            std::string temp(64 - buffer->size(),'0');
            *buffer += temp;
        }
        append_(fifter_,buffer);
        if(buffer->size() <= 128)
        {
            std::string temp(128-buffer->size(),'0');
            *buffer += temp;
        }
    }
    void clear(){
        if(file_size >  option_->write_()){
            restarte_.clear();
            fifter_.clear();
            indexblock_.clear();
            recode_.clear();
            bloom_.clear();
            if(number_.load(std::memory_order_relaxed) < 4)
            {
                number_.store(number_.load(std::memory_order_relaxed) + 1);
            }
        }
    }

private:
    struct recode{
    private:
        char * key_length;
        std::string key;
        char * value_length;
        sds value;
    public:
        bool operator < (recode & rhs){
            return this->key < rhs.key;
        }
        recode(std::string & key_ , sds &value_) :
                key(key_),value(value_){
            char data[5];
            bzero(data, sizeof(data));
            EncodeInt32(data,key_.size());
            key_length = new char[strlen(data)];
            strcpy(key_length,data);
            bzero(data, sizeof(data));
            EncodeInt32(data,value_.size());
            value_length = new char[strlen(data)];
            strcpy(value_length,data);
        }
        std::string key_(){
            return key;
        }
        std::string value_(){
            return value.Tostring();
        }
        std::string key_len(){
            return key_length;
        }
        std::string value_len(){
            return value_length;
        }
    };

    struct fifter{
        char begin[5]{};
        char  offest[5]{}; //每一块过滤的起始位置和偏移量
        fifter(uint32_t begin_ , uint32_t offest_ ) {
            EncodeInt32(begin,begin_);
            EncodeInt32(offest,offest_);
        }
    };

    struct index{
        char * key_length;
        sds key_; // 每一块最后的key
        char  *offest_; // 每一个数据块的偏移位置
        index(std::string & key,uint32_t offest) : key_(key){
            char data[5];
            bzero(data, sizeof(data));
            EncodeInt32(data,offest);
            offest_ = new char[strlen(data)];
            strcpy(offest_,data);
            bzero(data,sizeof(data));
            EncodeInt32(data,key_.size());
            key_length = new char[strlen(data)];
            strcpy(key_length,data);
        }
    };

private:
    std::vector<fifter> fifter_ ; //布隆过滤器的总目录
    std::vector<fifter> indexblock_ ; // 数据块的总目录
    std::vector<index> restarte_; // 重启点
    //重启点
    std::vector<recode> recode_; //数据块
    //总的过滤器 延长生命周期
    std::vector<std::shared_ptr<bloom>> bloom_;
    std::atomic_int idea_;// 对于重启点进行记录
    //必须限制sstable的个数多少
    std::atomic_int number_; // sstable的个数目前设置为4第一层
    std::unique_ptr<options> option_; // 对于选项参数设置
    unsigned long  long file_size ; // 目前已经存储块的长度

    std::string buffer_;
public:
    static void append_(std::vector<fifter> &p ,std::string * buffer)
    {
        for(auto &c : p)
        {
            buffer->append(std::to_string(std::to_string(strlen(c.begin)).size()));
            buffer->append(std::to_string(strlen(c.begin)));
            buffer->append(c.begin);
            buffer->append(std::to_string(std::to_string(strlen(c.offest)).size()));
            buffer->append(std::to_string(strlen(c.offest)));
            buffer->append(c.offest);
        }
    }

};

#endif //MY_REDIES_SSTABLE_H
