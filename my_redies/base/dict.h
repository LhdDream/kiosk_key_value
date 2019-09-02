//
// Created by kiosk on 19-8-26.
//

#ifndef MY_REDIES_DICT_H
#define MY_REDIES_DICT_H
#include "state.h"
#include <memory>
#include <vector>
#include <unordered_map> // 哈希表
#include <boost/any.hpp>
//实现哈希表
//dict 的特点，在于重哈希,采用增量方式的哈希，在需要扩展内存的时候
//避免一次性对于所有的key进行重哈希，
class dict
{
public:
    dict() : ht(new dictEntry(2)),iterators(0)
    {

    };
    ~dict(){};
    using  dictEntry = std::unordered_map<boost::any,boost::any>;
    using  dictpair = std::pair<boost::any,boost::any>;
    dictpair *dictFind(const void * key);
    int dictRehash();//每4096之后进行一次重哈希操作
    int dictAdd(void * key,void * val); //插入一个新的key和value
    int dictdel(void * key);
private:
   std::unique_ptr<dictEntry> ht;
   //目前正在进行的安全迭代器的数量
   int iterators;
};
#endif //MY_REDIES_DICT_H
