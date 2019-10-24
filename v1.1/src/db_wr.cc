//
// Created by kiosk on 19-9-22.
//
#include "db_wr.h"

status wr::Get( const sds &key, std::string *value) {
    return db::Get(key,value);
}
status wr::Delete(const  sds &key) {
    return db::Delete(key);
}
status wr::Set(const sds &key, const sds &value) {
    return db::Set(key,value);
}

wr::~wr() = default;

status db::Get(const sds &key, std::string *value) {
    write_->Get(key,value);
}
status db::Delete(const sds &key) {
    write_->Delete(key);
}
status db::Set(const  sds &key,const sds &value) {
    write_->Set(key,value);
}
