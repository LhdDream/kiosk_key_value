//
// Created by kiosk on 19-10-26.
//

#ifndef MY_REDIES_LRU_H
#define MY_REDIES_LRU_H

#include <unordered_map>
#include <list>
#include <cstddef>
#include <stdexcept>
#include "../base/sds.h"
#include "../base/options.h"
#include <string>



//在这里实现lru 策略
//设置过时时间淘汰相应的键
//lfu 暂时不进行考虑
//lru 在所有的key中找出一部分，找出距离现在距离最迟的key,并且进行淘汰
//根据超时时间来进行
//记录一下每一个元素的访问时间


class lru_cache{
public:
    using key_value_pair = std::pair<sds,sds>;
    using list_iterator_t = std::list<key_value_pair>::iterator;

    lru_cache() : option_(std::make_unique<options>()){}
    void put(const sds &key, const sds &value){
        auto it = _cache_map.find(key);
        _cache.push_front(key_value_pair(key,value));
        // 每次插入到队列首部
        if(it != _cache_map.end()){
            _cache.erase(it->second);
            _cache_map.erase(it);  //从hashmap中和list之中进行删除
        }
        _cache_map[key] = _cache.begin();
        // map之中指向list 的指针
        if(_cache_map.size() > option_->get_lru_number())
        {
            auto en = _cache.end();
            en--;
            _cache_map.erase(en->first);
            _cache.pop_back(); // 删除掉最后一位
        }
    }
    const sds & get(const sds & key){
        auto it = _cache_map.find(key);
        if(it != _cache_map.end())
        {
            _cache.splice(_cache.begin(),_cache,it->second);
            return it->second->second;
        }
    }
    bool exist(const sds & key){
        return _cache_map.find(key)!= _cache_map.end();
    }
    size_t  size () const {
        return _cache_map.size();
    }
private:
    std::list<key_value_pair> _cache;
    std::unordered_map<sds,list_iterator_t> _cache_map;
    std::unique_ptr<options> option_;
};
#endif //MY_REDIES_LRU_H
