//
// Created by kiosk on 19-9-22.
//

#ifndef MY_SIMPLE_STORAGE_DB_H
#define MY_SIMPLE_STORAGE_DB_H
//这里是数据库的总接口
#include <string>
class db{
public:
    db() = default;
    db(const db &) = delete;
    db& operator=(const db &) = delete;
    virtual ~db()  = default;
    virtual void Set(const std::string & key,const std::string &value) = 0;
    virtual void Delete(const std::string &key) = 0 ;
    virtual bool Get(const std::string &key,std::string & value) = 0;
    virtual bool Save() = 0 ;
};


#endif
