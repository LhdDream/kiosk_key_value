//
// Created by kiosk on 19-9-14.
//
#include "../util/bloom_filter.h"
#include <iostream>
int main()
{
    bloom<int> bloom_;
    bloom_.add(3);
    if(bloom_.Contaion(3))
    {
        std::cout<< "have " << std::endl;
    }
    bloom_.add(2);
    if(bloom_.Contaion(2))
    {
        std::cout << "you are" << std::endl;
    }
}
