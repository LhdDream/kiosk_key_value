//
// Created by kiosk on 19-9-3.
//
//this file reference leveldb
#ifndef MY_REDIES_PRENA_H
#define MY_REDIES_PRENA_H
//在这里构建了一个内存管理器
#include <atomic>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <memory>
class Prena
{
public:
    Prena();
    Prena(const Prena &) = delete; // 删除默认生成的赋值
    Prena& operator=(const Prena&) = delete;
    ~Prena();
    //return a pointer to a new allocated memory block
    char * allocate(size_t bytes);
    //使用malloc 正常对齐的方式来进行内存的申请
    char * defalutallocate(size_t bytes);
    size_t  Usage() const{
        return memory_usage.load(std::memory_order_relaxed);
        //内存序，仅仅在一个线程中保持happens-before 关系
        //acquire_release 表示在同一个原子变量中的release操作和acquire操作进行同步
        //同时建立起来执行序列的约束

    }
private:
    char * allocateFallback(size_t bytes);
    char * allocateNewBlock(size_t block_bytes);
    std::unique_ptr<char> alloc_ptr; //用来指向没有使用的起始地址
    size_t alloc_bytes_reamining_; // 当前所指向的内存块中还有多少内容可以进行使用
    std::vector<std::unique_ptr<char >> blocks;
    std::atomic<size_t> memory_usage;// 已经使用的内存
};
//if 0 bytes are requested , we should not allow processing
inline  char * Prena::allocate(size_t bytes) {
    assert(bytes > 0 );
    if(bytes <= alloc_bytes_reamining_)
    {
        char * result = alloc_ptr.get();
        alloc_ptr.reset(alloc_ptr.get() + bytes);
        alloc_bytes_reamining_ -= bytes;
        return result;
    }
    return allocateFallback(bytes);
}
#endif //MY_REDIES_PRENA_H
