//
// Created by kiosk on 19-10-14.
//

#ifndef MY_SIMPLE_STORAGE_ALLOCATE_H
#define MY_SIMPLE_STORAGE_ALLOCATE_H


#include <memory>
#include <atomic>
#include <atomic>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <memory>
#include "memorypool/memorypool.h"

template<class T, std::size_t growSize = 4096>
class Allocator : private MemoryPool<T, growSize> {
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T value_type;

    template<class U>
    struct rebind {
        typedef Allocator<U, growSize> other;
    };

    Allocator() noexcept = default;

    Allocator(const Allocator &) noexcept = default;

    template<class U>
    explicit Allocator(const Allocator<U> &) noexcept {}

    ~Allocator() noexcept = default;

    pointer allocate(size_type n, const void *hint = nullptr) {
        if (n <= 0 || hint)
            throw std::bad_alloc();
        return MemoryPool<T, growSize>::allocate(n);
    }

    void deallocate(pointer p, size_type n) {
        MemoryPool<T, growSize>::deallocate(p, n);
    }

    void construct(pointer p, const T &val) {
        new(p) T(val);
    }

    void destroy(pointer p) {
        p->~T(); // 调用析够函数
    }
};

#endif

