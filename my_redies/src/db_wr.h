//
// Created by kiosk on 19-9-22.
//

#ifndef MY_REDIES_DB_WR_H
#define MY_REDIES_DB_WR_H
#include <memory>
#include "../base/dict_builder.h"
#include "db.h"
#include "../base/options.h"

#include <atomic>
#include <string>
#include <deque>
#include <set>
#include "write_buffer.h"
class wr : public  db{
public:
    wr()= default;
    wr(const wr & )= delete;
    wr& operator =(const wr &) = delete;
    ~wr() override ; // override 确保派生类声明的重载函数
    //有相同的签名
    //签名不匹配会导致创建一个新的虚函数
    bool Set(const sds & key,const sds &value) override ;
    bool Delete(const sds &key) override ;
    bool Get(const sds &key,std::string * value) override ;

private:
    friend class db;
    struct Writer;
};
#endif //MY_REDIES_DB_WR_H
