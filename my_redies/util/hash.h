//
// Created by kiosk on 19-9-14.
//

#ifndef MY_REDIES_HASH_H
#define MY_REDIES_HASH_H
#include <iostream>
#include <cstring>
const int MOD = 10007;

unsigned int RSHash(const char* str)
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

unsigned int JSHash(const char* str)
{
    unsigned int hash = 1315423911;
    while (*str)
    {
        hash ^= ((hash << 5) + *str++ + (hash >> 2));
    }
    return (hash & 0x7fffffff) % MOD;
}

unsigned int PJWHash(const char* str)
{
    unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xffffffff) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    while (*str)
    {
        hash = (hash << OneEighth) + *str++;
        if((test = hash & HighBits)  != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return (hash & 0x7fffffff) % MOD;
}


unsigned int SDBMHash(const char* str)
{
    unsigned int hash = 0;
    while (*str)
    {
        hash = *str++ + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7fffffff) % MOD;
}

unsigned int APHash(const char* str)
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
