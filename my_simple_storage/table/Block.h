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
    size_t  m_offset = 0 ;
};

class Block::Itear {

public:
    Itear(const char * data,uint32_t off,uint32_t num):
            m_data(data),m_offset(off),m_num_offset(num)
    {   ReadOff();}
    std::string Key() { return m_key;}
    std::string Value() {return m_value;}
    bool Seek(const std::string &target);

private:
    const char* const m_data;
    uint32_t const m_offset;  //块中的偏移量开始的地方
    uint32_t const m_num_offset;// 有多少个块的偏移量
    std::string m_key;
    std::string m_value;
    std::vector<uint32_t > m_off ; // 表示所有的key_value的键值偏移量

    void ReadOff(){
        std::string everyoff_;
        uint32_t number = 0 ;
        m_off.emplace_back(number);
        for(size_t i = 0 ; i < m_num_offset ; i++)
        {
            everyoff_.resize(5,'\0');
            std::copy(m_data + m_offset +  i *4,m_data + m_offset + (i+1) *4 ,everyoff_.begin());
            number += DecodeInt32(everyoff_.data());
            m_off.emplace_back(number);
            //获取到每一个key_value 的偏移量
        }
    }
    uint32_t  GetoffestPoint(uint32_t index){
        return m_off[index - 1];
    }
};



#endif //MY_REDIES_BLOCK_H
