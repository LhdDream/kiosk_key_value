//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"
using namespace deconding;
template  <typename T>
bool dict<T>::Add(sds & key, T & value) {
    type _type;
    if(typeid(value)   == typeid(uint32_t)){
        SetInt32(_type.value_,value);
        _type.type_ = "uint32_t";
        ht_->insert({key,_type});
    }
    else if(typeid(value) == typeid(uint64_t)){
        SetInt64(_type.value_,value);
        _type.type_ = "uint64_t";
        ht_->insert({key,_type});
    }else if(typeid(value) == typeid(sds)){
        Setsds(_type.value_,value);
        _type.type_ = "sds";
        ht_->insert({key,_type});
    }else if(typeid(value) == typeid(parallel_flat_hash_set<T>)){

    }

}

template  <typename  T>
bool dict<T>::Get(sds &) {

}
