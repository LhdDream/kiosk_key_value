//
// Created by kiosk on 19-10-23.
//
#include <iostream>
#include "../src/db.h"
#include "../src/db_wr.h"
#include "../src/db_wr.cc"
using namespace std;

int main()
{
    db * db_ = new wr();
    std::string c = " aaaa";
    for(size_t i = 0 ;  i< 10000 ; i++)
    {
        db_->Set(std::to_string(i),c);
    }
    delete db_;
   return 0;
}
