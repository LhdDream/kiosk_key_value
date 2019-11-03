//
// Created by kiosk on 19-9-22.
//
#include "db_wr.h"

bool wr::Get( const sds &key, std::string *value) {
    return db::Get(key,value);
}
bool wr::Delete(const  sds &key) {
    return db::Delete(key);
}
bool wr::Set(const sds &key, const sds &value) {
    return db::Set(key,value);
}

wr::~wr() = default;

bool db::Get(const sds &key, std::string *value) {
    write_->Get(key,value);
}
bool db::Delete(const sds &key) {
    write_->Delete(key);
}

bool db::Set(const  sds &key,const sds &value) {
    write_->Set(key,value);
}
