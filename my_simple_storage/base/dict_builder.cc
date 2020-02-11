//
// Created by kiosk on 19-9-15.
//
#include "dict_builder.h"

void dict::Set(const std::string & key,  const std::string & value ) {
    //bloom 过滤器对于减少磁盘的IO查询起到了作用
    Save();
    m_log.info()  << key << ' '<< value << ' ';
    m_log.flunsh();
   if(m_lost.find(key) != m_lost.end()){
       m_lost.erase(key);
   }
    auto it = m_ht[m_index].find(key) ;
    if( it == m_ht[m_index].end() ) {
        m_buffer_size += key.size();
        m_buffer_size += value.size();
        m_ht[m_index].emplace(key,value);
        m_lru->Put(key,value);
    }else{
        m_ht[m_index][key] = value;
        m_lru->Put(key,m_ht[m_index][key]);
    }
}

bool dict::Get(const std::string &key, std::string &value) {
    if(m_lost.find(key) != m_lost.end()){
        return false;
    }
    if(m_lru->Exist(key) ) {
          value = m_lru->Get(key);
          return true;
    }else {
        int i = m_index;
        while(i >= 0) {
            auto c = m_ht[i].find(key);
            if (c != m_ht[i].end() ) {
                value = c->second;
                return true;
            }
            i--;
        }
        return  m_sstable->Get(key,value);
        //磁盘中读取
    }
}

void  dict::Delete(const std::string &key) {
    m_lost.emplace(key);
}

bool dict::Save() {
    if(options::GetOptions().Block() <= m_buffer_size){
        m_write_size += m_buffer_size;
        m_buffer_size = 0;
        m_index++;
    }else if(options::GetOptions().Write() <= m_write_size){
        //进行异步save
        if(options::GetOptions().Id() % 5 == 0 && (options::GetOptions().Write() <= m_number)){
            options::GetOptions().AddBlock();
            options::GetOptions().AddWrite();
        }
        Map c;
        Merge(m_ht[m_index - 2], m_ht[m_index], c);
        m_sstable->UnmemtableAdd(c);
        m_sstable->Write_NameFile();
        m_write_size = 0;
        m_index = 0;
        m_log.clear();
    }
    return true;
}

void dict::Merge(Map &a, Map &b, Map &c) {
    for(const auto  & l : b){
        if(m_lost.find(l.first) == m_lost.end())
            c.emplace(l.first,l.second);
    }
    for(const auto & l :a){
        if(m_lost.find(l.first) == m_lost.end())
             c.emplace(l.first,l.second);
    }
    a.clear();
    b.clear();
}

void dict::Recover( const std::string &filename) {
    if( !access(filename.data(),0)){
        //创建一个文件流对象，并打开文件
        std::ifstream fin(filename.c_str());
        //创建字符串流对象
        std::stringstream sin;
        sin <<  fin.rdbuf();
        std::string p;
        std::string key;
        std::string value;
        bool ty = true;
        while(getline(sin,p,' ')){
            if(ty){
                key = p;
                ty = false;
            }else{
                value =p;
                m_ht[m_index].emplace(key,value);
                ty = true;
            }
        }
        fin.close();
        fin.clear();
        remove(filename.c_str());
    }
}