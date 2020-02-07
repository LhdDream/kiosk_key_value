//
// Created by kiosk on 19-9-22.
//
#include "db_wr.h"

bool wr::Get( const sds &key, std::string *value) {
    return  write_->Get(key,value);
}
bool wr::Delete(const  sds &key) {
    return  write_->Delete(key);
}
void wr::Set(const sds &key, const sds &value) {
     write_->Set(key,value);
}

bool wr::save() {
    return  write_->save();
}
