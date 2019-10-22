//
// Created by kiosk on 19-10-20.
//

#include <iostream>
#include "../base/decondig.h"
#include "../base/decondig.cc"
int main(){
    std::string c = "Nothing is more difficult, and therefore more precious, than to be able to decide";
 //   char d[4096];
//   auto *d = new std::vector<char>();
   std::string d;
  // d.resize(10);
   // d[3] = 'c';
    deconding::smaz_compress(c.data(),c.size(),&d);
    std::cout << d<< std::endl;
    std::string p ;
    deconding::smaz_decompress(d.data(),d.size(),&p);
    std::cout << p << std::endl;
}
//"\000\000L\376T8\254>\255\230>\303F" L�T8�>��>�F
//"\376TL8\254>\255\230>\303F" �TL8�>��>�F
