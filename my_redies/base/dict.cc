//
// Created by kiosk on 19-8-26.
//
#include <assert.h>
#include <algorithm>
#include "dict.h"
dict::dictpair * dict::dictFind(const void *key)
{
   if(ht.get()[0].size() + ht.get()[1].size() == 0)
       return NULL; // 说明没有内容
    if(ht.get()[0].size() % 4096 == 0) // 重哈希
    {
        //把重哈希推进一步
        dictRehash();
    }
    for(size_t i = 0 ; i <= 2 ; ++i) {
           if(ht.get()[i].find(key) != ht.get()[i].end())
           {
              std::pair<boost::any,boost::any> tmp(key,ht.get()[i][key]);
              return &tmp;
              //返回一个键值对
           }
        if(ht.get()[0].size() == 0) return NULL;
    }
    return NULL;
}
int dict::dictRehash() {
    ht.get()[0].swap(ht.get()[1]);
}
//添加一个键值对进入到字典之中
//这里如果有的话直接进行覆盖,没有的话将其添加
int dict::dictAdd(void *key, void *val) {
    if(ht.get()[0].size() % 4096 == 0) {
        dictRehash();
        ht.get()[1][key] = val;
    }
    else
    {
        ht.get()[0][key] = val;
    }
    return DICT_OK;
}
int dict::dictdel(void *key) {
    if(ht.get()[0].size() %4096  == 0)
    {
        dictRehash();
        if(ht.get()[1].find(key) == ht.get()[1].end())
        {
            return DICT_ERR;
        }
        else
        {
            ht.get()[1].erase(key);
        }
    }
    else
    {
        if(ht.get()[0].find(key) == ht.get()[0].end())
        {
            return DICT_ERR;
        }
        else
        {
            ht.get()[0].erase(key);
        }
    }

}


