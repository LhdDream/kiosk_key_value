//
// Created by kiosk on 19-10-1.
//

#ifndef MY_REDIES_SSTABLE_H
#define MY_REDIES_SSTABLE_H

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <snappy.h>
#include <map>
#include <list>
#include "../base/options.h"
#include "../base/sds.h"
#include "../util/bloom_filter.h"
#include "block_builder.h"
#include "../util/memorypool/memorypool.h"
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
    sstable(std::shared_ptr<options> op_) :writ_ (nullptr),blo(std::make_unique<block_builder>()) , option_(op_)
    {
        std::cout << "writesss" << std::endl;
        data_index.emplace_back(0);
        fifter_index.emplace_back(0);
    };
    ~sstable() = default;
    void unmemtableadd(std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> & value ){
        for(auto &it : *value)
        {
            blo->Add(it.first, it.second);
        }
        buffer_.append(blo->finish()); //
        unmemtable_.emplace_back(std::move(value));
       //这里应该是data_index上一块加+
        data_index.emplace_back(buffer_.size());
        //快进行组织
        fifter_buffer+= blo->to_fif(); // fiter 过滤器
        fifter_index.emplace_back(fifter_buffer.size());
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
            offest_.append(bufs, sizeof(bufs));
        }
        offest_ += '\r';
    }
    void write_namefile()
    {
        buffer_ += fifter_buffer;
        compostionoffest(data_index);
        compostionoffest(fifter_index);
        {
            char bufs[4];
            bzero(bufs, sizeof(bufs));
            EncodeInt32(bufs, data_index.size() + fifter_index.size());
            offest_.append(bufs,sizeof(bufs));
            buffer_.append(offest_);
            for(auto & it : data_index)
            {
                std::cout << it  << std::endl;
            }
        }
        std::string filename;
        option_->makefilename(&filename);
        writ_ = std::make_unique<write_file>(filename);
        writ_->writeFile(buffer_.data(),buffer_.size());
        Reset();
    }
    void Reset(){
        fifter_buffer.clear();
        buffer_.clear();
        data_index.clear();
        fifter_index.clear();
        offest_.clear();
        unmemtable_.pop_front(); // 每次把第一个清除掉
        data_index.emplace_back(0);
        fifter_index.emplace_back(0);
    }

private:
    std::unique_ptr<write_file> writ_;
    std::unique_ptr<block_builder> blo;
    std::list<std::unique_ptr<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>>> > unmemtable_;
    // 转化为有序的map进行存储
    std::shared_ptr<options> option_; // 对于选项参数设置
    std::string buffer_; // 写入文件的内容
private:
    std::vector<uint32_t > data_index; //　每一个数据块的index
private:
    std::string fifter_buffer; // fifter 中的buffer
    std::vector<uint32_t > fifter_index; // index 标记
private:
    std::string offest_ ; //偏移量的offest
};

#endif //MY_REDIES_SSTABLE_H
