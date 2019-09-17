//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"
using namespace deconding;
template  <typename T>
bool dict<T>::Add(sds & key, T & value) {
    type _type = dict<T>::type();
    if(typeid(value)   == typeid(uint32_t)){
        SetInt32(_type.value_,value);
        _type.type_ = "0";
        ht_->insert({key,_type});
    }
    else if(typeid(value) == typeid(uint64_t)){
        SetInt64(_type.value_,value);
        _type.type_ = "1";
        ht_->insert({key,_type});
    }else if(typeid(value) == typeid(sds)){
        Setsds(_type.value_,value);
        _type.type_ = "2";
        ht_->insert({key,_type});
    }else if(typeid(value) == typeid(std::vector<std::string>)){
        _type.type_ = "3";
        Setset(_type.value_,value);
        ht_->insert({key,_type});
    }
    type__->push_back(_type);
}
