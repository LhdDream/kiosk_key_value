//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"
#include <snappy.h>

void dict::Add(const sds & key,const  sds & value) {
    //返回相应的方式
    if((options_->block_() <= buffer_size) && (options_->write_() > buffer_size)){
        sstable_->bloomadd(bloom_);
        sstable_->save();
        bloom_ = std::make_shared<bloom> ();
    }
    if(list_->size() >= options_->get_lru_number()) {
        PDelete();
    }
        //bloom 过滤器对于减少磁盘的IO查询起到了作用
        if(ht_->find(key) == ht_->end()) {
            sstable_->add(key.Tostring(), const_cast<sds &>(value));
            Put(key);
            bloom_->add(key);
            //对于大型的value 进行压缩
            snappy::Compress(value.data(), value.size(), &buffer);
            buffer_size += buffer.size();
            buffer_size += key.size();
            ht_->emplace(key, buffer);
        }else{
            ht_->at(key) = value;
            auto it = std::find(list_->begin(),list_->end(),key);
            list_->splice(list_->begin(),*list_,it);
    }
}

bool dict::Get(const sds &key, std::string *value) {
        if( ht_->find(key) != ht_->end())
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
    if(ht_->find(key) != ht_->end()){
        if(list_->size() == options_->get_lru_number())
                PDelete();
         ht_->erase(key);
         return true;
    }
    return false;
}

void dict::PDelete(){
    ht_->erase(list_->back()) ;
    list_->pop_back();
}
void dict::Put(const sds & key) {
     if(list_->size() >= options_->get_lru_number())
     {
        PDelete();
     }
     list_->push_front(key);
}

