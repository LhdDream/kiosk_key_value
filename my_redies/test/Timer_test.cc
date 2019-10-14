//
// Created by kiosk on 19-10-6.
//
#include <iostream>
#include "../base/sds.h"
#include <unistd.h>
#include <map>
#include "../util/Allocate.h"
#include <list>
#include <set>
struct c
{
    bool operator()(const sds &x ,const sds &y) const {
        return x.Tostring() < y.Tostring();
    }
};
int main()
{
    std::list<int,Allocator<int>> c;
    c.push_front(1);
    for(auto p  : c)
    {
        std::cout << p <<std::endl;
    }
    return 0;
}
