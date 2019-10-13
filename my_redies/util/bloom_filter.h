//
// Created by kiosk on 19-9-14.
//

#ifndef MY_REDIES_BLOOM_FILTER_H
#define MY_REDIES_BLOOM_FILTER_H
#include <bitset>
#include "hash.h"
#include <functional>
#include <vector>
#include <any>
#include "../base/sds.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
//this file create bloom
//bloom 过滤器表示如果不在这个集合之中，则说明不在，在这个集合之后，实时不一定在这个集合之中
class bloom
{
public:
    bloom(){
        array.reset();
    }
    void add(const sds &Temp);


private:
    std::bitset<16 * 1024> array; //2KB
};

 void  bloom::add(const sds &Temp) {
        array.set(SDBMHash(Temp.data()));
        array.set(RSHash(Temp.data()));
        array.set(JSHash(Temp.data()));
        array.set(APHash(Temp.data()));
        array.set(PJWHash(Temp.data()));
}


#endif //MY_REDIES_BLOOM_FILTER_H
