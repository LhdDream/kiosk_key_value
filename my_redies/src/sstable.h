//
// Created by kiosk on 19-10-1.
//

#ifndef MY_REDIES_SSTABLE_H
#define MY_REDIES_SSTABLE_H

#include <vector>
#include <string>
#include "../base/options.h"
#include <algorithm>
#include "../base/sds.h"
#include "../util/bloom_filter.h"
#include <snappy.h>
//
//fifter
//block
//总目录
//静态索引一层，数据一层
class sstable{
public:
    sstable() = default;
    ~sstable() = default;
    void add(std::string & key,sds &value)
    {
        recode_.emplace_back(key,value);
    }
    void bloomadd(std::unique_ptr<bloom> &&bl){
        bloom_.emplace_back(std::move(bl));
    }
private:
    struct fifter{
        uint32_t  begin;
        uint32_t  offest; //每一块过滤的起始位置和偏移量
    };
    std::vector<fifter> fifter_ ; //布隆过滤器的总目录
    struct index{
       sds key_; // 每一块最后的key
       uint32_t  offest; // 每一个数据块的偏移位置
    };
    std::vector<index> index_;//生成一块静态索引
    std::vector<index> restarte_; // 重启点
    //重启点
    struct recode{
    private:
         uint16_t key_length;
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
    };
    std::vector<recode> recode_; //数据块
    //总的过滤器 延长生命周期
    std::vector<std::unique_ptr<bloom>> bloom_;
};

#endif //MY_REDIES_SSTABLE_H
