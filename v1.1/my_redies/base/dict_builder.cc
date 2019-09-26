//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"
#include <snappy.h>

void dict::Add(const sds & key,const  sds & value) {
    bloom_->add(key); // 对于bloom过滤器
    //对于大型的value 进行压缩
    snappy::Compress(value.data(),value.size(),&buffer);
    ht_->emplace(key,buffer);
}

bool dict::Get(const sds &key, std::string *value) {
        if(bloom_->Contaion(key))
        {
           // 如果找到则进行解码操作
           auto c = ht_->find(key);
           if(c != ht_->end())
           {
               snappy::Uncompress(c->second.data(),c->second.size(),value);
               return true;
           }
        }
        return false;
}

bool dict::Delete(const sds &key) {
    if(bloom_->Contaion(key)){
         ht_->erase(key);
         return true;
    }
    return false;
}