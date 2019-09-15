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
//this file create bloom
//bloom 过滤器表示如果不在这个集合之中，则说明不在，在这个集合之后，实时不一定在这个集合之中
template <typename T>   class bloom
{
public:
    bloom(){
        array.reset();
    }
    void add(const T &Temp);
    bool Contaion(const T & temp);
private:
    std::bitset<1024000> array;
};

template<typename T>  void  bloom<T>::add(const T &Temp) {
        if(array.count() >= 1020000)
        {
            array.reset();
        }
        array.set(SDBMHash(std::to_string(Temp).c_str()));
        array.set(RSHash(std::to_string(Temp).c_str()));
        array.set(JSHash(std::to_string(Temp).c_str()));
        array.set(APHash(std::to_string(Temp).c_str()));
        array.set(PJWHash(std::to_string(Temp).c_str()));
        array.set(ELFHash(std::to_string(Temp).c_str()));
}

template <typename T > bool bloom<T>::Contaion(const T &Temp) {
        return array.test(SDBMHash(std::to_string(Temp).c_str()))
        && array.test(RSHash(std::to_string(Temp).c_str()))
        && array.test(JSHash(std::to_string(Temp).c_str()))
        && array.test(APHash(std::to_string(Temp).c_str()))
        && array.test(PJWHash(std::to_string(Temp).c_str()))
        && array.test(ELFHash(std::to_string(Temp).c_str()));
        ;
}
#endif //MY_REDIES_BLOOM_FILTER_H
