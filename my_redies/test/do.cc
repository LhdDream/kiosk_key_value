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
using  namespace std;


int main()
{
   std::unordered_map<sds,sds> s;
   s.emplace("A","b");
    s.emplace("f","a");
    s.emplace("l","s");
    std::map<sds,sds> odered(s.begin(),s.end());
    for(auto & c : odered){
        std::cout << c.first.Tostring() << std::endl;
    }
    return 0;
}
