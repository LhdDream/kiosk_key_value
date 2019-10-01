//
// Created by kiosk on 19-9-22.
//
#include "../src/db.h"
#include "../src/db_wr.h"
#include "../src/db_wr.cc"
#include<iostream>

int main()
{
   db * db_ = new wr();
   std::string temp("ddd");
   std::string temp_("lll");
   std::string p;
   db_->Set(temp,temp_);
   db_->Get(temp,&p);
   std::cout << p << std::endl;
   return 0;
}
