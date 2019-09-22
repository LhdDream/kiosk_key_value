//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"
using namespace deconding;
template  <typename T>
bool dict<T>::Add(sds & key, T & value) {
    type _type = dict<T>::type();
    bloom_->add(key); // 对于bloom过滤器
    std::string buf;
    if(typeid(value)   == typeid(uint32_t)){
        SetInt32(&buf,value);
        _type.value_ = buf;
        _type.type_ = "0";
        ht_->insert({key,_type});
    }
    else if(typeid(value) == typeid(uint64_t)){
        SetInt64(&buf,value);
        _type.value_ = buf;
        _type.type_ = "1";
        ht_->insert({key,_type});
    }else if(typeid(value) == typeid(sds)){
        Setsds(&buf,value);
        _type.value_ = buf;
        _type.type_ = "2";
        ht_->insert({key,_type});
    }else if(typeid(value) == typeid(skiplist<sds>))
    {
        _type.type_ = "3";
        _type.value_ = value;
        ht_->insert({key,_type});
    }
    type__->push_back(_type);
}
template <typename  T>
bool dict<T>::Get(sds &key, std::string *value) {
        if(bloom_->Contaion(key))
        {
            //如果找到则进行解码操作
           if(ht_->find(key) != ht_->end())
           {
               switch (ht_[key]._type)
               {
                   case "0":{
                       GetInt32(std::any_cast<sds>(ht_[key]._value),value);
                       break;
                   }
                   case "1":{
                       GetInt64(std::any_cast<sds>(ht_[key]._value),value);
                       break;
                   }
                   case "2":{
                       GetSds(std::any_cast<sds>(ht_[key]._value),value);
                       break;
                   }
                   case "3":{
                       //skiplist
                       skiplist<sds> temp = std::any_cast<skiplist<sds>>(ht_[key]._value);
                       temp.print();
                       break;
                   }
               }
           }
        }
        return false;
}