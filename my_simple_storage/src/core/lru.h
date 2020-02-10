//
// Created by kiosk on 19-10-26.
//

#ifndef MY_SIMPLE_STORAGE_LRU_H
#define MY_SIMPLE_STORAGE_LRU_H

#include <unordered_map>
#include <list>
#include <cstddef>
#include <string>



//在这里实现lru 策略
//设置过时时间淘汰相应的键
//lfu 暂时不进行考虑
//lru 在所有的key中找出一部分，找出距离现在距离最迟的key,并且进行淘汰
//根据超时时间来进行
//记录一下每一个元素的访问时间

class lru_cache{
public:
    using key_value_pair = std::pair<std::string,std::string>;
    using list_iterator_t = std::list<key_value_pair>::const_iterator;

    lru_cache() = default;

    void Put(const std::string &key, const std::string &value){
        m_cache.push_front(key_value_pair(key,value));
        // 每次插入到队列首部
        auto it = m_cache_map.find(key);
        if(  it !=m_cache_map.end()){
            m_cache.erase(it->second);
            m_cache_map.erase(it);  //从hashmap中和list之中进行删除
        }
        m_cache_map[key] = m_cache.begin();
        // map之中指向list 的指针
        if(m_cache_map.size() > options::GetOptions().Get_Lru_Number())
        {
            auto en = m_cache.end();
            en--;
            m_cache_map.erase(en->first);
            m_cache.pop_back(); // 删除掉最后一位
        }
    }
    const std::string & Get(const std::string & key){
        auto it = m_cache_map.find(key);
        if(it != m_cache_map.end()  )
        {
            m_cache.splice(m_cache.begin(),m_cache,it->second);
            return it->second->second;
        }
    }
    bool Exist(const std::string & key){
        auto it = m_cache_map.find(key);
        return it!= m_cache_map.end() ;
    }
    size_t  Size () const {
        return m_cache_map.size();
    }
private:
    std::list<key_value_pair> m_cache;
    std::unordered_map<std::string,list_iterator_t> m_cache_map;
};



#endif //MY_REDIES_LRU_H
