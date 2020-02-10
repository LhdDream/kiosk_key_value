//
// Created by kiosk on 19-9-15.
//

#ifndef MY_SIMPLE_STORAGE_DICT_BUILDER_H
#define MY_SIMPLE_STORAGE_DICT_BUILDER_H

#include <algorithm>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <wait.h>
#include "../log/Log.h"
#include "../src/core/db.h"
#include "../config/options.h"
#include "../table/sstable.h"
#include "../util/memorypool/memorypool.h"
#include "../table/block_builder.h"
#include "../src/core/lru.h"
//在这里使用内存表的构建


class dict : public  db
{
public:
    using Map = std::map<std::string,std::string,std::less<>,MemoryPool<std::pair<std::string,std::string>>>;
public:
        explicit dict(const std::string &filename) :m_index(0),m_ht(4),m_lru(std::make_unique<lru_cache>()),
         m_buffer_size{},
         m_sstable(std::make_unique<sstable>()),
         m_write_size{}{
//            Recover(filename);
//            Logger::init(filename,true);
        }
        dict(const dict & ) = delete ;
        dict&operator = (const dict &) = delete;
        ~dict() override = default;

        void Set(const std::string & ,const std::string &) override ;
        bool Get(const std::string &,std::string &) override ;// 查找
        void Delete(const std::string &) override ;
        bool Save() override ;

        static std::unique_ptr<dict> Init(const std::string &filename, const std::string &name){
            options::GetOptions().SetFilename(name);
            return std::make_unique<dict>(filename);
        }
        void Merge( Map & a ,  Map &b, Map &c);
        void Recover( const std::string & filename);
private:
    Logger m_log;
    int m_index = 0 ;
    std::vector<Map>  m_ht;
    std::unique_ptr<lru_cache> m_lru ;
    unsigned long long m_buffer_size ;
    std::unique_ptr<sstable> m_sstable; // sstable
    unsigned  long long m_write_size ;
};


#endif //MY_REDIES_DICT_BUILDER_H
