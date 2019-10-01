//
// Created by kiosk on 19-10-1.
//

#ifndef MY_REDIES_SSTABLE_H
#define MY_REDIES_SSTABLE_H
//计划使用sstable 方式存入在磁盘中，尽可能存入海量的数据
//
#include <vector>
#include <string>
#include "../base/options.h"
class sstable{
public:
private:
    std::vector<std::string> key_buffer; // key buffer
    std::vector<std::string> value_buffer;  // value 的bufffer
    size_t  key_size;
    size_t  value_size;
};
#endif //MY_REDIES_SSTABLE_H
