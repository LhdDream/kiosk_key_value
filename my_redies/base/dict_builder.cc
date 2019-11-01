//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"

void dict::Add(const sds & key,const  sds & value) {
    //返回相应的方式
    if((options_->block_() <= buffer_size) && (options_->write_() > buffer_size)){
        sstable_->unmemtableadd(ht_);
        ht_ = std::make_unique<std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>> >>();
    }else if(options_->write_() < buffer_size)
    {
        sstable_->write_namefile();
        buffer_size = 0 ;
    }
    //bloom 过滤器对于减少磁盘的IO查询起到了作用
    if(ht_->find(key) == ht_->end()) {
        lru_->put(key,value);
        //对于大型的value 进行压缩
        buffer_size += key.size();
        buffer_size += value.size();
        ht_->emplace(key,value);
    }else{
        ht_->at(key) = value;
        lru_->put(key,value);
    }
}

bool dict::Get(const sds &key, std::string *value) {
    if(lru_->exist(key)) {
          *value = lru_->get(key).Tostring();
    }else {
        auto c = ht_->find(key);
        if (c!= ht_->end()) {
            // 如果找到则进行解码操作
                *value = c->second.Tostring();
                return true;
        }else {
            sstable_->Get(const_cast<sds &>(key), value);
        }
    }
    return false;
}

bool dict::Delete(const sds &key) {
    if(ht_->find(key) != ht_->end()){
         ht_->erase(key);
         return true;
    }
    return false;
}


