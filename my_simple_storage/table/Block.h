//
// Created by kiosk on 19-10-17.
//

#ifndef MY_SIMPLE_STORAGE_BLOCK_H
#define MY_SIMPLE_STORAGE_BLOCK_H
//sstable 中所构建的数据块
#include <unistd.h>
#include <cstdint>
#include <snappy.h>
#include <vector>
#include <memory>
#include "../base/decondig.h"
#include <iostream>
using namespace deconding;

class Block{
public:
    explicit Block() = default;
    ~Block() = default;
    class Itear;

    std::unique_ptr<Itear> newItear(const char * data_,int len);
private:
    size_t  m_offest = 0 ;
};

class Block::Itear {
private:
    const char* const data_;
    uint32_t const offest_;  //块中的偏移量开始的地方
    uint32_t const num_offest_;// 有多少个块的偏移量
    uint32_t offest_index_; //读取第几个的key_value
    std::string key_;
    std::string value_;
    std::vector<uint32_t > off_ ; // 表示所有的key_value的键值偏移量
public:
    Itear(const char * data,uint32_t off,uint32_t num):
            data_(data),offest_(off),num_offest_(num),
            offest_index_(num)
    {   ReadOff();}

private:
    void ReadOff(){
        std::string everyoff_;
         uint32_t number = 0 ;
        off_.emplace_back(number);
        for(size_t i = 0 ; i < num_offest_ ; i++)
        {
            everyoff_.resize(5,'\0');
            std::copy(data_ + offest_ +  i *4,data_+offest_ + (i+1) *4 ,everyoff_.begin());
            number += DecodeInt32(everyoff_.data());
            off_.emplace_back(number);
            //获取到每一个key_value 的偏移量
        }
    }
private:
    uint32_t  GetoffestPoint(uint32_t index){
        return off_[index - 1];
    }
public:
    std::string Key() { return key_;}
    std::string Value() {return value_;}
    bool Seek(const std::string &target);
};



#endif //MY_REDIES_BLOCK_H
