#ifndef MY_SIMPLE_STORAGE_BLOOM_FILTER_H
#define MY_SIMPLE_STORAGE_BLOOM_FILTER_H
#include "hash.h"
#include <vector>
//this file create bloom
//bloom 过滤器表示如果不在这个集合之中，则说明不在，在这个集合之后，实时不一定在这个集合之中
//bloom 参考leveldb 的实现方式来进行实现
class bloom
{
public:
    explicit bloom( ) : m_bits_per_key(0) ,m_h(0){
    }
    void Add(const std::string &key, std::string & result_){
        //每次调用写入一个key
        m_bits_per_key = key.size() * 8;
        //对齐，方便内存读写以及后续位置的索引
        auto bytes = (m_bits_per_key + 7)/8;
        m_bits_per_key = bytes * 8;
        //向下取整
        result_.resize(bytes ,0);
        m_h = APHash(key.data());
        auto  delta = (m_h >> 17) | (m_h << 15);
        for (size_t j = 0; j < 4; j++) {
            // 在整个bit 数组的位置
            auto  bitpos = m_h % (m_bits_per_key );
            // 在char型数组的位置
            result_[bitpos/8] |= (1 << (bitpos % 8));
            // 更新获得一个新的hash 数值
            m_h += delta;
        }
    }
    bool Key_Match(const  std::string & key,std::string & result_){
        if (result_.empty()) {
            return false;
        }
        m_h = APHash(key.data());
        auto delta = (m_h >> 17) | (m_h << 15);
        auto array = result_.data();

        m_bits_per_key = key.size() * 8;
        //对齐，方便内存读写以及后续位置的索引
        auto bytes = (m_bits_per_key + 7)/8;
        m_bits_per_key = bytes * 8;

        for (size_t j = 0; j < 4; j++) {
            // 在整个bit 数组的位置
            auto bitpos = m_h % (m_bits_per_key);
            // 在char型数组的位置
            if ((array[bitpos / 8] & (1 << (bitpos % 8))) == 0)
                return false;
            // 更新获得一个新的hash 数值
            m_h += delta;
        }
        return true;
    }
private:
    size_t  m_bits_per_key;   //每一个key拥有的bit数目 // 一般为１0
    uint32_t  m_h ;
};
#endif //MY_REDIES_BLOOM_FILTER_H
