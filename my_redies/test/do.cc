//
// Created by kiosk on 19-9-22.
//
#include "../src/db.h"
#include "../src/db_wr.h"
#include "../src/db_wr.cc"
#include<iostream>
#include<map>
#include "../util/sparsepp/spp.h"
#include <unordered_map>
#include "../base/sds.h"
using namespace std;
using spp::sparse_hash_map;


int main()
{
   int start = clock();
   sparse_hash_map<sds,sds> c;
   db * db_ = new wr();
   for(size_t i = 0 ; i < 1000; i++)
   {
       db_->Set(std::to_string(i),"aaa");
   }
   delete  db_;
    printf("%.3lf/n",double(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
