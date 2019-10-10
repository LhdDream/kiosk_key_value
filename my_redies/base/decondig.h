#ifndef MY_REDIES_ZIPLIST_H
#define MY_REDIES_ZIPLIST_H
//打算使用snappy来进行解压缩
#include <snappy.h> //
#include "sds.h"
#include <string>
#include <vector>
#include <any>
#include "skiplist.h"

namespace deconding{
    // 在这里里面实现get , set 方法相应对象的编码方式
    // varint 变长整形
    void EncodeInt32(char *intput  ,uint32_t value);
    uint32_t DecodeInt32(const char * ptr);
}
#endif //MY_REDIES_ZIPLIST_H