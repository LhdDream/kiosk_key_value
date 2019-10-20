//
// Created by kiosk on 19-10-17.
//

#ifndef MY_REDIES_BLOCK_H
#define MY_REDIES_BLOCK_H
//sstable 中所构建的数据块
#include <unistd.h>
#include <cstdint>
#include "../base/decondig.h"
#include "../base/decondig.cc"
using namespace deconding;
// 每一个数据块中的最后维护
class Block{
public:
    [[nodiscard]] size_t  size() const {
        return size_;
    }
    ~Block(){
        delete  [] data;
    }

private:
     [[nodiscard]] uint32_t numrestarts() const {
        return DecodeInt32(data + size_ - sizeof(uint32_t));
    }; //返回重启点的个数

    const char * data;
    size_t size_;
    uint32_t offest_; // 重启点的偏移量
};
#endif //MY_REDIES_BLOCK_H
