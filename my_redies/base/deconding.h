//
// Created by kiosk on 19-9-3.
//

#ifndef MY_REDIES_ZIPLIST_H
#define MY_REDIES_ZIPLIST_H
//打算使用snappy来进行解压缩
#include <snappy.h> //
#include "sds.h"
#include "dict.h"
#include <string>
#include <set>
//compress 压缩
//uncompress 解压缩
//特殊编码的linklist 提高存储效率，存储字符串或者整数
//这里进行编码的压缩
//snappy
//the different objects of this file are encoded
//different objects are encoded different object
//内存屏障，确保特定操作执行的顺序，影响一些数据的可见性
namespace deconding{
    // 在这里里面实现get , set 方法相应对象的编码方式
    // varint 变长整形
    void SetInt32(std::string *dst ,uint32_t value);
    void SetInt64(std::string * dst ,uint64_t value);
    void Setsds(std::string  *dst, std::string value);
    //整数集合 intset
    void Setintset(std::string * dst,std::set<int> value);
    //内部以sds进行存储
    //这里的string底部是以sds方式来进行实现
    //进行底层的压缩
    //转化为二进制来进行存储节省宽度　编码为varint
    char * EncodeInt32(sds *dst ,uint32_t value);
    char * EncodeInt64(sds * dst, uint64_t value);
    const char * EncodeSds(sds * dst, std::string value);
    uint32_t  DecodeInt32(const char * ptr);
    uint64_t DecodeInt64(const char * ptr);
    std::string DecodeSds(const char * ptr);
}
#endif //MY_REDIES_ZIPLIST_H

