//
// Created by kiosk on 19-10-20.
//
#include <iostream>
#include "../util/bloom_filter.h"

using namespace std;
int main()
{
    std::string p;
    bloom c;
    c.add("aaa",&p);
    if(c.key_match("aaa",&p)) {
        std::cout << "true" << std::endl;
    }else
    {
        std::cout << "kkk" << std::endl;
    }
    c.add("akljsfklasjfksaf",&p);
    if(c.key_match("akljsfklasjfksaf",&p)){
        std::cout << "true" << std::endl;
    }
//    c.add("askjfyhqwiuyrtghjhAVFmnbdvs",&p);
//
//
//    if(c.key_match("askjfyhqwiuyrtghjhAVFmnbdvs",&p))
//    {
//        std::cout << "true" << std::endl;
//    }
//    return 0;
}