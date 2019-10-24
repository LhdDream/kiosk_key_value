//
// Created by kiosk on 19-10-16.
//
#include "memorypool.h"


template <typename T, size_t BlockSize>
void
MemoryPool<T, BlockSize>::allocateBlock()
{
    auto newBlock = static_cast<char *> (operator new(BlockSize));
    // new
    reinterpret_cast<DATA_ *>(newBlock)->next = currentBlock_;
    //使用尾插
    currentBlock_ = reinterpret_cast<DATA_ *>(newBlock);
    //创建出一个新块
    char * body_ = newBlock + sizeof(DATA_ *);

    auto  res = reinterpret_cast<uintptr_t >(body_);
    // 为了类型安全
    size_t bodyoffest = ((alignof(DATA_) - res) % alignof(DATA_));
    //计算类型字节数超出指针多少? //方便内存对齐
    //alignof 表示内存对齐的大小结构体中
    currentSlot_ = reinterpret_cast<DATA_ *>(body_ + bodyoffest);
    lastSlot_ = reinterpret_cast<DATA_ *> (newBlock + BlockSize - sizeof(DATA_) + 1);
    //块的最后一块指针
}



template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::pointer
MemoryPool<T, BlockSize>::allocate(size_t n, const_pointer hint )
{
    if(n <= 0  )
        throw std::bad_alloc();
    if (freeSlots_ != nullptr) {
        auto result = reinterpret_cast<pointer>(freeSlots_);
        freeSlots_ = freeSlots_->next;
        return result;
        //找到一块空闲块并且返回出去
    }
    else {
        if (currentSlot_ >= lastSlot_) // 说明剩余下来的块不够使用
            allocateBlock(); // 重新创建一个块出来
        return reinterpret_cast<pointer>(currentSlot_++);
    }
}



template <typename T, size_t BlockSize>
inline void
MemoryPool<T, BlockSize>::deallocate(pointer p, size_t n)
{
    if (p != nullptr) {
        reinterpret_cast<DATA_ *>(p)->next = freeSlots_;
        freeSlots_ = reinterpret_cast<DATA_ *>(p);
        //链表删除
    }
}


template <typename T, size_t BlockSize>
template <class U, class... Args>
inline void
MemoryPool<T, BlockSize>::construct(U* p, Args&&... args)
{
    new (p) U (std::forward<Args>(args)...);
    //使用可变参数模板和完美转发转化为右值
}


template <typename T, size_t BlockSize>
template <class U>
inline void
MemoryPool<T, BlockSize>::destroy(U* p)
{
    p->~U();
}

