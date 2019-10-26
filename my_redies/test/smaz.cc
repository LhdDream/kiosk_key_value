//
// Created by kiosk on 19-10-20.
//
#include <snappy.h>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include "../base/decondig.h"
#include "../base/decondig.cc"
using namespace std;
using namespace deconding;
std::string c()
{
    std::string p = "A";
    return p;
}
int main() {
    std::vector<uint32_t > p;
    char bufs[4];
    std::string buffer_;
    for(size_t i = 0 ; i< 100000 ; i++)
    {
        p.emplace_back(i);
    }
    for(auto & it : p)
    {
        EncodeInt32(bufs,it);
        buffer_ += bufs;
    }
    EncodeInt32(bufs,p.size());
    buffer_ += bufs;
    std::cout << buffer_.size() << std::endl;
    return 0;
}