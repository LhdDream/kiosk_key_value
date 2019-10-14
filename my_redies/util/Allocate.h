//
// Created by kiosk on 19-10-14.
//

#ifndef MY_REDIES_ALLOCATE_H
#define MY_REDIES_ALLOCATE_H


#include <memory>
#include <atomic>
#include <atomic>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <memory>
template <class T, std::size_t growSize = 1024>
class MemoryPool
{
    struct Block
    {
        Block *next;
    };

    class Buffer
    {
        static const std::size_t blockSize = sizeof(T) > sizeof(Block) ? sizeof(T) : sizeof(Block);
        uint8_t data[blockSize * growSize]{};

    public:

        Buffer *const next;

        explicit Buffer(Buffer *next) :
                next(next)
        {
        }

        T *getBlock(std::size_t index)
        {
            return reinterpret_cast<T *>(&data[blockSize * index]);
        }
    };

    Block *firstFreeBlock = nullptr;
    Buffer *firstBuffer = nullptr;
    std::size_t bufferedBlocks = growSize;


public:

    MemoryPool() = default;
    MemoryPool(MemoryPool &&memoryPool) = delete;
    MemoryPool(const MemoryPool &memoryPool) = delete;
    MemoryPool operator =(MemoryPool &&memoryPool) = delete;
    MemoryPool operator =(const MemoryPool &memoryPool) = delete;

    ~MemoryPool()
    {
        while (firstBuffer) {
            Buffer *buffer = firstBuffer;
            firstBuffer = buffer->next;
            delete buffer;
        }
    }

    T *allocate()
    {
        if (firstFreeBlock) {
            Block *block = firstFreeBlock;
            firstFreeBlock = block->next;
            return reinterpret_cast<T *>(block);
        }

        if (bufferedBlocks >= growSize) {
            firstBuffer = new Buffer(firstBuffer);
            bufferedBlocks = 0;
        }

        return firstBuffer->getBlock(bufferedBlocks++);
    }

    void deallocate(T *pointer)
    {
        auto *block = reinterpret_cast<Block *>(pointer);
        block->next = firstFreeBlock;
        firstFreeBlock = block;
    }
};


template <class T, std::size_t growSize = 4096>
class Allocator : private MemoryPool<T, growSize>
{
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T value_type;

    template <class U>
    struct rebind
    {
        typedef Allocator<U, growSize> other;
    };
    Allocator() noexcept = default;
    Allocator(const Allocator&) noexcept  = default;

    template <class U> explicit Allocator(const Allocator<U>&) noexcept{}

    ~Allocator() noexcept  = default;
    pointer allocate(size_type n, const void *hint = nullptr)
    {
        if (n <= 0 || hint)
            throw std::bad_alloc();
        return MemoryPool<T, growSize>::allocate();
    }

    void deallocate(pointer p, size_type )
    {
        MemoryPool<T, growSize>::deallocate(p);
    }

    void construct(pointer p, const T& val)
    {
        new (p) T(val);
    }
    void destroy(pointer p)
    {
        p->~T(); // 调用析够函数
    }
};

#endif

