//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"
#include <snappy.h>

void dict::Add(const sds & key,const  sds & value) {
    //返回相应的方式
    if(options_->write_() <= buffer_size){
            sstable_->swap(ht_);
            sstable_->save(bloom_);
            buffer_size = 0 ;
    }
    if( Getlru(key)){
        ht_->at(key) = value;
    }
    else {
        //bloom 过滤器对于减少磁盘的IO查询起到了作用
        Put(key);
        bloom_->add(key);
        //对于大型的value 进行压缩
        snappy::Compress(value.data(), value.size(), &buffer);
        buffer_size += buffer.size();
        buffer_size += key.size();
        ht_->emplace(key, buffer);
    }
}

bool dict::Get(const sds &key, std::string *value) {
        if( Getlru(key))
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
    if(Getlru(key)){
        if(list_->size() == options_->get_lru_number())
                PDelete();
         ht_->erase(key);
         return true;
    }
    return false;
}

void dict::PDelete(){
    ht_->erase(*(--list_->end()));
    list_->erase(--list_->end());//位置
}
void dict::Put(const sds & key) {
    auto c = std::find(list_->begin(),list_->end(),key) ;
    if( c != list_->end())
    {
        list_->erase(c++);
    }
    if(list_->size() == options_->get_lru_number())
    {
        PDelete();
        list_->emplace_front(key);
        //进行删除
        //被动删除策略
    }else{
        list_->emplace_front(key);
    }
}

bool dict::Getlru(const sds & key) {
       return std::find(list_->begin(),list_->end(),key) != list_->end();
}