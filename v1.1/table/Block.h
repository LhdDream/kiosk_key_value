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
    explicit Block(const sds & data_) : data(data_.data()),size_(data_.size()){

    }
    [[nodiscard]] size_t  size() const {
        return size_;
    }
    ~Block(){
        delete  [] data;
    }

private:
    const char * data;
    size_t size_;

};
#endif //MY_REDIES_BLOCK_H
