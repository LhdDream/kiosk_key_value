//
// Created by kiosk on 19-10-17.
//

#ifndef MY_REDIES_BLOCK_H
#define MY_REDIES_BLOCK_H
//sstable 中所构建的数据块
#include <unistd.h>
#include <cstdint>

class Block{
public:
    [[nodiscard]] size_t  size() const {
        return size_;
    }
    ~Block(){
        delete  [] data;
    }

private:
    uint32_t numrestarts() const {

    }; //返回重启点的个数
    const char * data;
    size_t size_;
    uint32_t offest_; // 重启点的偏移量
};
#endif //MY_REDIES_BLOCK_H
