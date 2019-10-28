//
// Created by kiosk on 19-9-14.
//

#ifndef MY_REDIES_BLOOM_FILTER_H
#define MY_REDIES_BLOOM_FILTER_H
#include "hash.h"
#include <vector>
#include "../base/sds.h"
//this file create bloom
//bloom 过滤器表示如果不在这个集合之中，则说明不在，在这个集合之后，实时不一定在这个集合之中
//bloom 参考leveldb 的实现方式来进行实现
class bloom
{
public:
    explicit bloom( ) : bits_per_key(0) ,offest_(0),h(0){
    }
    void add(const sds &key,std::string * result_){
        //每次调用写入一个key
        bits_per_key = key.size() * 8;
        //有多少位
        if(bits_per_key < 64)
            bits_per_key = 64;
        //对齐，方便内存读写以及后续位置的索引

        auto bytes = (bits_per_key + 7)/8;
        bits_per_key = bytes * 8;
        //向下取整
        auto init_size = 0;
        if(!result_->empty())
        {
            init_size = result_->size();
        }
        offest_ += bytes;
        result_->resize(init_size + bytes ,0);

        auto  array = reinterpret_cast<char *> (&(*result_)[init_size]);

        h = APHash(key.data());
        auto  delta = (h >> 17) | (h << 15);
        for (size_t j = 0; j < 4; j++) {
            // 在整个bit 数组的位置
            auto  bitpos = h % (bits_per_key );
            // 在char型数组的位置
            array[bitpos/8] |= (1 << (bitpos % 8));
            // 更新获得一个新的hash 数值
            h += delta;
        }
    }
    bool key_match(const sds & key,std::string * result_){
            if (result_->empty()) {
                return false;
            }
            h = APHash(key.data());
            auto delta = (h >> 17) | (h << 15);
            auto array = result_->data();
            for (size_t j = 0; j < 4; j++) {
                // 在整个bit 数组的位置
                auto bitpos = h % (bits_per_key);
                // 在char型数组的位置
                if ((array[bitpos / 8] & (1 << (bitpos % 8))) == 0)
                    return false;
                // 更新获得一个新的hash 数值
                h += delta;
            }
        return true;
    }
private:
    size_t  bits_per_key;   //每一个key拥有的bit数目 // 一般为１0
    size_t offest_{};
    uint32_t  h ;
};
#endif //MY_REDIES_BLOOM_FILTER_H
