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
#include "block_builder.h"
#include "block_builder.cc"
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
    sstable() :writ_ (nullptr),blo(std::make_unique<block_builder>()) , option_(std::make_unique<options>()),seqnumber_(0)
    {
    };
    ~sstable() = default;
    void unmemtableadd(std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> & value ){
        for(auto &it : *value)
        {
            blo->Add(const_cast<sds &>(it.first), it.second);
        }
        buffer_ +=  blo->finish(); //
        unmemtable_.emplace_back(std::move(value));
        data_index.emplace_back(blo->buffer_size());
        //快进行组织
        seqnumber_ += buffer_.size();
        blo->Reset();
    }
    void bloomadd(std::shared_ptr<bloom> & b){
        bloom_.emplace_back(std::move(b));
        seqnumber_ += 2048;
    }
    bool Get(sds & key_,std::string *value){
        for(auto &c :unmemtable_)
        {
            if(c->find(key_) != c->end()){
                 *value = c->at(key_).Tostring();
                return true;
            }
        }
        return false;
    }
    void composition_file(){
        for(auto & it  : bloom_)
        {
            buffer_ += it->append();
            fifter_index++;
        }
        //现在把各个块的偏移量进行写入, 如果不满多少字节则进行补充
      //  compostionoffest(data_index);
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
        buffer_ += bufs;
        bzero(bufs,sizeof(bufs));
        EncodeInt32(bufs,fifter_index);
        buffer_ += bufs;
    }
    void write_namefile()
    {
        composition_file();
        std::string filename =  "."+std::to_string(id_) + "tts";
        writ_ = std::make_unique<write_file>(filename);
        writ_->writeFile(buffer_.data(),buffer_.size());
        buffer_.clear();
        write_.emplace_back(std::move(writ_));
        printf("write_namefile\n");
    }
private:
    std::unique_ptr<write_file> writ_;
    std::vector<std::shared_ptr<bloom>> bloom_;
    std::unique_ptr<block_builder> blo;
    std::vector<std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> > unmemtable_;
    // 转化为有序的map进行存储
    std::unique_ptr<options> option_; // 对于选项参数设置
    unsigned long long seqnumber_; //
    std::string buffer_; // 写入文件的内容
    std::vector<std::unique_ptr<write_file>> write_; // 标志写入文件
private:
    std::vector<uint32_t > data_index; //　每一个数据块的index
    uint32_t fifter_index{}; // fifter 的个数　，　每一块的大小相同
    static long long id_ ;
};
long long sstable::id_ = 0;
#endif //MY_REDIES_SSTABLE_H
