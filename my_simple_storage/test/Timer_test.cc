//
// Created by kiosk on 19-10-6.
//
#include <iostream>
#include "../base/sds.h"
#include <unistd.h>
#include <map>
//#include "../util/Allocate.h"
#include <list>
#include <set>
#include "../util/memorypool/memorypool.h"
#include "../util/memorypool/memorypool.cc"
struct c
{
    bool operator()(const sds &x ,const sds &y) const {
        return x.Tostring() < y.Tostring();
    }
};
int main()
{
    std::map<sds,sds,c,MemoryPool<std::pair<sds,sds>>> c;\
    c.emplace("1","@");

    return 0;
}
