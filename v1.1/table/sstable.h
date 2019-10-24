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
#include "../base/decondig.h"
#include "../base/decondig.cc"
#include "../util/bloom_filter.h"
#include "../base/options.h"
#include "../util/sparsepp/spp.h"
#include "../util/memorypool/memorypool.h"
#include "../util/memorypool/memorypool.cc"
#include "write_file.h"
using spp::sparse_hash_map;
using namespace deconding;
//fifter
//block
//总目录
//静态索引一层，数据一层
//先进行顺序读取
//索引加具体内容
//总索引
//fifter
//data block = restart
//思路，先读取所有的整个索引，如果不满48字节，进行补充到 48 字节
//首先把然后通过判断每一个索引块来进行编写
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
            if(c->find(key_) != c->end()){
                snappy::Uncompress(c->at(key_).data(),c->at(key_).size(),value);
                return true;
            }
        }
        return false;
    }
    void file_Get(){
        if(seqnumber_ >= option_->write_())
        {
            // 进行写入
            write_.emplace_back(std::make_unique<write_file>("."+std::to_string(seqnumber_)+ "tts"));
            //
        }
    }

private:
    std::vector<std::shared_ptr<bloom>> bloom_;
    std::vector<std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> > unmemtable_;
    // 转化为有序的map进行存储
    std::unique_ptr<options> option_; // 对于选项参数设置
    unsigned long long seqnumber_; //
    std::string buffer_; // 写入文件的内容
    std::vector<std::unique_ptr<write_file>> write_; // 标志写入文件


};

#endif //MY_REDIES_SSTABLE_H
