//
// Created by kiosk on 19-9-3.
//

#ifndef MY_REDIES_ZIPLIST_H
#define MY_REDIES_ZIPLIST_H
//打算使用snappy来进行解压缩
#include "sds.h"
#include <string>
#include <vector>
//the different objects of this file are encoded
//different objects are encoded different object

namespace deconding{
    // 在这里里面实现get , set 方法相应对象的编码方式
    // varint 变长整形
    //set 直接使用skiplist
    //整数集合 intset
    //进行底层的压缩
    //转化为二进制来进行存储节省宽度　编码为varint
    unsigned char * EncodeInt32(unsigned char *intput  ,uint32_t value);
    unsigned char * EncodeInt64(unsigned char *intput , uint64_t value);
    uint32_t  DecodeInt32(const  char * ptr);
    uint64_t DecodeInt64(const char * ptr);
}
#endif //MY_REDIES_ZIPLIST_H