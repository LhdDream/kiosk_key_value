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
typedef struct dictType {
    // 计算哈希值的函数
    unsigned int (*hashFunction)(const void *key);
    // 复制键的函数
    void *(*keyDup)(void *privdata, const void *key);
    // 复制值的函数
    void *(*valDup)(void *privdata, const void *obj);
    // 对比键的函数
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);
    // 销毁键的函数
    void (*keyDestructor)(void *privdata, void *key);
    // 销毁值的函数
    void (*valDestructor)(void *privdata, void *obj);
} dictType;

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
    struct Dict
    {
       dictType *type; //   用于特定类型
       void * privdata;
    };
};
#endif //MY_REDIES_DICT_H
