//
// Created by kiosk on 19-10-23.
//
#include <iostream>
//#include "leveldb/db.h"
#include <iostream>
#include "../src/db.h"
#include "../src/db_wr.h"
#include "../src/db_wr.cc"
using namespace std;

int main()
{
//    leveldb::DB *db;
//    leveldb::Options options;
//    options.create_if_missing = true;
//    leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
//    assert(status.ok());
    db * db_ = new wr();
    std::string c = " aaaa";
    std::string p;
    for(size_t i = 0 ;  i< 10000 ; i++)
    {
       db_->Set(std::to_string(i),c);
    }
    delete db_;
   return 0;
}
