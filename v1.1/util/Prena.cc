//
// Created by kiosk on 19-9-3.
//
#include "Prena.h"
static  const int Blocksize = 8192;

Prena::Prena()
    : alloc_ptr(nullptr),alloc_bytes_reamining_(0) , memory_usage(0){
}

Prena::~Prena() {
    for(auto &c :blocks)
    {
        delete [] c;
    }
}
char* Prena::allocateFallback(size_t bytes) {
    if(bytes > Blocksize / 8)
    {
        //if > 1/8  重新创建一个新块出来
        char * result = allocateNewBlock(bytes);
        return result;
    }
    alloc_ptr = allocateNewBlock(Blocksize);
    alloc_bytes_reamining_ = Blocksize;

    char * result = alloc_ptr;
    alloc_ptr = alloc_ptr + bytes;
    alloc_bytes_reamining_ -= bytes;
    return result;
}
//内存回收对齐的收集函数 allocatealigned . 相比于前面

char* Prena::defalutallocate(size_t bytes) {
    //64 位机上的指针占8个字节，方便内存对齐
    const int size = 8 ;
    size_t  mod = reinterpret_cast<uintptr_t >(alloc_ptr) &(size - 1);
    // 查看对齐了多少位
    size_t  slop = ((mod == 0) ? 0 : size - mod);
    //查看有多少为还需要补充
    size_t needed = bytes + slop;
    char * result;
    if(needed <= alloc_bytes_reamining_)
    {
        result = alloc_ptr + slop;
        alloc_ptr = alloc_ptr + needed;
        alloc_bytes_reamining_ -= needed;
    } else {
        result = allocateFallback(bytes); //重新创造一个新块
    }
    return result;
}



char* Prena::allocateNewBlock(size_t block_bytes) {
    char * result = new char[block_bytes];
    blocks.emplace_back(result);
    memory_usage.fetch_add(block_bytes + sizeof(char*),std::memory_order_relaxed);
    return result;
}