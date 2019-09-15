//
// Created by kiosk on 19-9-15.
//
#include <../util/parallel_hashmap/phmap.h>
#include <iostream>
#include <string>
using phmap::parallel_flat_hash_map;
int main()
{
    parallel_flat_hash_map<std::string,std::string> email =
            {
                    {"hhh" , "ddd"}
            };
    email.insert({"sss","sss"});
    for(auto &c : email)
    {
        std::cout << c.first << std::endl;
    }
    return 0;
}
