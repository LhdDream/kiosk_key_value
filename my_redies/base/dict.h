//
// Created by kiosk on 19-8-26.
//

#ifndef MY_REDIES_DICT_H
#define MY_REDIES_DICT_H
#include "state.h"
#include <map>
#include <memory>
//实现内存哈希表
//支持插入,删除，替换，查找和获取随机元素
//哈希表会自动在表的大小二次方来进行调整
//键通过链表来进行解决
template <class t ,class t1>
class dict
{
public:
private:
    // 哈希表
    static std::map<t,t1> dictEntry;
    struct dictht
    {
        std::unique_ptr<std::unique_ptr<dictEntry>> table;
        //哈希表的大小
        unsigned long size;
        //哈希表的掩码大小
        unsigned long sizemask;
        //二进制的全１表示
        unsigned long used;
    };
};
#endif //MY_REDIES_DICT_H
