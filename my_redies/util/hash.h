//
// Created by kiosk on 19-9-14.
//

#ifndef MY_REDIES_HASH_H
#define MY_REDIES_HASH_H
#include <iostream>
#include <cstring>
const int MOD = 10007;

static unsigned int RSHash(const char* str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * a + *str++;
        a *= b;
    }
    return (hash & 0x7fffffff) % MOD;
}


static       unsigned int SDBMHash(const char* str)
{
    unsigned int hash = 0;
    while (*str)
    {
        hash = *str++ + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7fffffff) % MOD;
}

static unsigned int APHash(const char* str)
{
    unsigned int hash = 0xAAAAAAAA;
    for(int i = 0; str[i] != 0; ++i)
    {
        hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                (~((hash << 11) + (str[i] ^ (hash >> 5))));
    }
    return (hash & 0x7fffffff) % MOD;
}
#endif //MY_REDIES_HASH_H
