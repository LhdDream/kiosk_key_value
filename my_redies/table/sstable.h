//
// Created by kiosk on 19-10-1.
//

#ifndef MY_REDIES_SSTABLE_H
#define MY_REDIES_SSTABLE_H

#include <vector>
#include <string>
#include <memory>
#include <snappy.h>
#include <map>
#include "../base/options.h"
#include "../base/sds.h"

#include "../util/bloom_filter.h"
#include "../base/options.h"
#include "../util/sparsepp/spp.h"
#include "../util/memorypool/memorypool.h"
#include "../util/memorypool/memorypool.cc"
#include "write_file.h"
using spp::sparse_hash_map;
//fifter
//block
//总目录
//静态索引一层，数据一层
class bloom;
class options;
class sstable{
public:
    sstable() :
    option_(std::make_unique<options>()),seqnumber_(0)
    {

    };
    ~sstable() = default;
    void unmemtableadd(std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> & value , unsigned long long size){
        unmemtable_.emplace_back(std::move(value));
        seqnumber_ += size; // 找到多大
    }
    void bloomadd(std::shared_ptr<bloom> & b){
        bloom_.emplace_back(std::move(b));
        seqnumber_ += 2048;
    }
    bool Get(sds & key_,std::string *value){
        for(auto &c :unmemtable_)
        {
            if(c.find(key_) != c.end()){
                snappy::Uncompress(c.at(key_).data(),c.at(key_).size(),value);
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::shared_ptr<bloom>> bloom_;
    std::vector<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> unmemtable_;
    // 转化为有序的map进行存储
    std::unique_ptr<options> option_; // 对于选项参数设置
    unsigned long long seqnumber_; //
    std::string buffer_; // 写入文件的内容
};

#endif //MY_REDIES_SSTABLE_H
