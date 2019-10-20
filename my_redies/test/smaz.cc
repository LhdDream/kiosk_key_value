//
// Created by kiosk on 19-10-20.
//

#include <iostream>
#include "../base/decondig.h"
#include "../base/decondig.cc"
int main(){
    std::string c = "aaa";
    std::string d;
    deconding::smaz_compress(c,c.size(),&d);
    std::cout << d.data() << std::endl;
}

