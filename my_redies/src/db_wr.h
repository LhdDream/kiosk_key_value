//
// Created by kiosk on 19-9-22.
//

#ifndef MY_REDIES_DB_WR_H
#define MY_REDIES_DB_WR_H
#include <memory>
#include <atomic>
#include <string>
#include <deque>
#include <set>
#include "db.h"
#include "write_buffer.h"
class wr : public  db{
public:
    wr() :write_(std::make_unique<write_buffer>()){

    };
    wr(const wr & )= delete;
    wr& operator =(const wr &) = delete;
    ~wr() override = default; // override 确保派生类声明的重载函数
    //有相同的签名
    //签名不匹配会导致创建一个新的虚函数
    void  Set(const sds & key,const sds &value) override ;
    bool Delete(const sds &key) override ;
    bool Get(const sds &key,std::string * value)  override ;
    bool save() override ;
private:
    friend class db;
    std::unique_ptr<write_buffer> write_;
};
#endif //MY_REDIES_DB_WR_H
