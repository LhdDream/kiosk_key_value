//
// Created by kiosk on 19-8-26.
//
#include <assert.h>
#include <algorithm>
#include "dict.h"
dict::dictpair * dict::dictFind(std::string &&key)
{
   if(ht[0].size() + ht[1].size() == 0)
       return NULL; // 说明没有内容
    if(ht[0].size() % 4096 == 0) // 重哈希
    {
        //把重哈希推进一步
        dictRehash();
    }
    for(size_t i = 0 ; i <= 2 ; ++i) {
               if(ht[i].find(key) != ht[i].end())
               {
                   dictpair  temp = std::make_pair(key,ht[i][key]);
                   return &temp;
               }
        if(ht[0].size() == 0) return NULL;
    }
    return NULL;
}
int dict::dictRehash() {
    ht[0].swap(ht[1]);
}
//添加一个键值对进入到字典之中
//这里如果有的话直接进行覆盖,没有的话将其添加
int dict::dictAdd(std::string &&key, void *val) {
    if(ht[0].size() % 4096 == 0) {
        dictRehash();
        ht[1][key] = val;
    }
    else
    {
        ht[0][key] = val;
    }
    return DICT_OK;
}
int dict::dictdel(std::string &&key) {
    if(ht[0].size() %4096  == 0)
    {
        dictRehash();
        if(ht[1].find(key) == ht[1].end())
        {
            return DICT_ERR;
        }
        else
        {
            ht[1].erase(key);
        }
    }
    else
    {
        if(ht[0].find(key) == ht[0].end())
        {
            return DICT_ERR;
        }
        else
        {
            ht[0].erase(key);
        }
    }
    return DICT_OK;
}


