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
    sstable() :writ_ (nullptr),blo(std::make_unique<block_builder>()) , option_(std::make_unique<options>())
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
        fifter_buffer += blo->to_fif(); // fiter 过滤器
        fifter_index.emplace_back(fifter_index.size());
        blo->Reset();
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
        buffer_ += bufs;
    }
    void write_namefile()
    {
        buffer_ += fifter_buffer;
      //  compostionoffest(fifter_index);
       // compostionoffest(data_index);
        std::string filename =  "."+std::to_string(id_) + "tts";
        writ_ = std::make_unique<write_file>(filename);
        writ_->writeFile(buffer_.data(),buffer_.size());
        write_.emplace_back(std::move(writ_));
    }
private:
    std::unique_ptr<write_file> writ_;
    std::unique_ptr<block_builder> blo;
    std::vector<std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> > unmemtable_;
    // 转化为有序的map进行存储
    std::unique_ptr<options> option_; // 对于选项参数设置
    std::string buffer_; // 写入文件的内容
    std::vector<std::unique_ptr<write_file>> write_; // 标志写入文件
private:
    std::vector<uint32_t > data_index; //　每一个数据块的index
    static long long id_ ;
private:
    std::string fifter_buffer; // fifter 中的buffer
    std::vector<uint32_t > fifter_index; // index 标记
};
long long sstable::id_ = 0;
#endif //MY_REDIES_SSTABLE_H
