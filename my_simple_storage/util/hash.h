//
// Created by kiosk on 19-9-14.
//

#ifndef MY_SIMPLE_STORAGE_HASH_H
#define MY_SIMPLE_STORAGE_HASH_H

#include <cstring>
#include <iostream>

// hash算法
static constexpr const int MOD = 10007;

static unsigned int APHash(const char* str) {
    unsigned int hash = 0xAAAAAAAA;
    for (int i = 0; str[i] != 0; ++i) {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ str[i] * (hash >> 3)) : (~((hash << 11) + (str[i] ^ (hash >> 5))));
    }
    return (hash & 0x7fffffff) % MOD;
}

#endif  // MY_REDIES_HASH_H
