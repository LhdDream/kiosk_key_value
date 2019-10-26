//
// Created by kiosk on 19-10-17.
//

#ifndef MY_REDIES_BLOCK_H
#define MY_REDIES_BLOCK_H
//sstable 中所构建的数据块
#include <unistd.h>
#include <cstdint>
#include "../base/sds.h"
#include "../base/decondig.h"
using namespace deconding;
// 每一个数据块中的最后维护
class Block{
public:
    explicit Block(const sds & data_) : data(data_.data()),size_(data_.size()){
        if(size_ < sizeof(uint32_t))
        {
            size_ = 0 ;//出现错误
        }
        else{
             offest_ = size_ - (1 + numrestarts() * sizeof(uint32_t));
             //块中的offest的偏移量
        }
    }
    [[nodiscard]] size_t  size() const {
        return size_;
    }
    ~Block(){
        delete  [] data;
    }
    [[nodiscard]] uint32_t numrestarts() const {
        return DecodeInt32(data + size_ - sizeof(uint32_t));
    }; //返回offest 的个数
private:
    const char * data;
    size_t size_;
    class Itear;
    Itear * newIteratr();
    uint32_t  offest_  ;// offest 的刚开始的地方
};
#endif //MY_REDIES_BLOCK_H
