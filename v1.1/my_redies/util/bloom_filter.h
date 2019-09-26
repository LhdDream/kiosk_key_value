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
#include "../base/dict_builder.h"
//this file create bloom
//bloom 过滤器表示如果不在这个集合之中，则说明不在，在这个集合之后，实时不一定在这个集合之中
class bloom
{
public:
    bloom(){
        array.reset();
    }
    void add(const sds &Temp);
    bool Contaion(const sds & temp);
private:
    std::bitset<1024000> array;
};

 void  bloom::add(const sds &Temp) {
        if(array.count() >= 1020000)
        {
            array.reset();
        }
        array.set(SDBMHash(Temp.data()));
        array.set(RSHash(Temp.data()));
        array.set(JSHash(Temp.data()));
        array.set(APHash(Temp.data()));
        array.set(PJWHash(Temp.data()));
        array.set(ELFHash(Temp.data()));
}

 bool bloom::Contaion(const sds &Temp) {
        return array.test(SDBMHash(Temp.data()))
        && array.test(RSHash(Temp.data()))
        && array.test(JSHash(Temp.data()))
        && array.test(APHash(Temp.data()))
        && array.test(PJWHash(Temp.data()))
        && array.test(ELFHash(Temp.data()));
        ;
}
#endif //MY_REDIES_BLOOM_FILTER_H
