//
// Created by kiosk on 19-9-22.
//

#ifndef MY_REDIES_DB_H
#define MY_REDIES_DB_H
//这里是数据库的总接口
#include "../base/options.h"
#include "../base/sds.h"
#include "write_buffer.h"
#include <memory>

class db{
public:
    db():write_(std::make_unique<write_buffer>()){
    };
    db(const db &) = delete;
    db& operator=(const db &) = delete;
    virtual ~db()  = default;
    virtual bool Set(const sds & key,const sds &value) = 0;
    virtual bool Delete(const sds &key) = 0 ;
    virtual bool Get(const sds &key,std::string * value) = 0;
private:
    std::unique_ptr<write_buffer> write_;
};
#endif
