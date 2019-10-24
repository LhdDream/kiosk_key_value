//
// Created by kiosk on 19-10-23.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <snappy.h>
#include "../base/decondig.h"
#include "../base/decondig.cc"
using namespace std;
using namespace deconding;
int main()
{
    char s [6];
   uint32_t  c = 1024;
   deconding::EncodeInt32(s,c);
   uint32_t  p = 2;
   std::string l;
   l += s;
   std::cout << l <<std::endl;
   std::cout << deconding::DecodeInt32(s) << std::endl;
   return 0;
}
