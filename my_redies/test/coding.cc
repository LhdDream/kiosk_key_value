//
// Created by kiosk on 19-9-10.
//
#include "../base/deconding.cc"
#include <iostream>
using  namespace deconding;

int main()
{
    uint64_t  b = 5123;
    char buf[1024];
    bzero(buf,sizeof(char) * 1024);
    unsigned char * temp =  EncodeInt64(buf,b);
    std::cout << temp << std::endl;
    uint64_t  c = 0 ;
    c = DecodeInt64(temp);
    std::cout << " c " << c << std::endl;
}
