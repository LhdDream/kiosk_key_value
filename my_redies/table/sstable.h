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
#include "block_builder.h"
#include "block_builder.cc"
#include "Block.h"
#include "Block.cc"
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
    sstable() :option_(std::make_unique<options>()),seqnumber_(0)
    {
    };
    ~sstable() = default;
    void unmemtableadd(std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> & value , unsigned long long size){

        std::unique_ptr<block_builder> blo = std::make_unique<block_builder>();

        for(auto &it : *value)
        {
            blo->Add(const_cast<sds &>(it.first), it.second);
        }
        buffer_ +=  blo->finish(); //
        unmemtable_.emplace_back(std::move(value));
        data_index.emplace_back(blo->buffer_size());
         // 写入第一块的大小
        block_.emplace_back(std::move(blo));
        //快进行组织
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
    void composition_file(){
        fifter_index.emplace_back(buffer_.size());
        for(auto & it  : bloom_)
        {
            buffer_ += it->append();
            fifter_index.emplace_back(buffer_.size());
        }
        //现在把各个块的偏移量进行写入, 如果不满多少字节则进行补充
        compostionoffest(fifter_index);
        compostionoffest(data_index);
    }
    void compostionoffest(std::vector <uint32_t > &index){
        char bufs[4];
        for(auto & it : index)
        {
            bzero(bufs,sizeof(bufs));
            EncodeInt32(bufs,it);
            buffer_ += bufs;
        }
        bzero(bufs,sizeof(bufs));
        EncodeInt32(bufs,data_index.size());
        buffer_.append(bufs,sizeof(bufs));
    }
    void write_namefile()
    {
        std::unique_ptr<write_file> writ_ = std::make_unique<write_file>("."+std::to_string(id_) + "tts");
        writ_->Append(buffer_);
        buffer_.clear();
        write_.emplace_back(writ_);
    }
private:
    std::vector<std::shared_ptr<bloom>> bloom_;

    std::vector<std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> > unmemtable_;
    // 转化为有序的map进行存储
    std::unique_ptr<options> option_; // 对于选项参数设置
    unsigned long long seqnumber_; //
    std::string buffer_; // 写入文件的内容
    std::vector<std::unique_ptr<write_file>> write_; // 标志写入文件
private:
    std::vector<uint32_t > data_index; //　每一个数据块的index
    std::vector<uint32_t > fifter_index; // 每一个bloom过滤器的index
    std::vector<std::unique_ptr<block_builder> > block_; // 每一个数据块的
    static long long id_ ;
};
long long sstable::id_ = 0;
#endif //MY_REDIES_SSTABLE_H
