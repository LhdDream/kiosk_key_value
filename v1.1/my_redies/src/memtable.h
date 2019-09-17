//
// Created by kiosk on 19-9-17.
//

#ifndef MY_REDIES_MEMTABLE_H
#define MY_REDIES_MEMTABLE_H
#include "../util/Prena.h"
#include "../base/skiplist.h"
#include "../base/dict_builder.h"
#include "../base/options.h"
//将memtable 内存表存储 把最新的插入的数据存储到内存表之中，超过一定值
//将内存表写入到磁盘之中
//使用mmap进行可靠性的存储
//kill -9
class memtable{
public:
    memtable(const memtable &) = delete;
    memtable& operator =(const memtable&) = delete;
private:
    //add 方案，跳跃表存入key,从内部构建的table
    //申请的内存
};
#endif //MY_REDIES_MEMTABLE_H
