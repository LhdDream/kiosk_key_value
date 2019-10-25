//
// Created by kiosk on 19-10-15.
//

#ifndef MY_REDIES_MEMORYBLOCK_H
#define MY_REDIES_MEMORYBLOCK_H
#include <climits>
#include <cstddef>
#include <utility>
#include <cstdint>
#include <memory>
template <typename T, size_t BlockSize = 4096>
class MemoryPool
{
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef const T*        const_pointer;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
    typedef std::false_type propagate_on_container_copy_assignment;
    typedef std::true_type  propagate_on_container_move_assignment;
    typedef std::true_type  propagate_on_container_swap;
    //编译期限中的true和false
    template <typename U> struct rebind {
        typedef MemoryPool<U> other;
    };

    MemoryPool() noexcept{
        currentBlock_ = nullptr;
        currentSlot_ = nullptr;
        lastSlot_ = nullptr;
        freeSlots_ = nullptr;
    };
    MemoryPool(const MemoryPool& memoryPool) noexcept = delete;
    MemoryPool(MemoryPool&& memoryPool) noexcept = delete;
    ~MemoryPool()  {
        auto  curr = currentBlock_;
        while (curr != nullptr) {
            auto prev = curr->next;
            delete curr;
            curr = prev;
        }
    };

    MemoryPool& operator=(const MemoryPool& memoryPool) = delete;
    MemoryPool& operator=(MemoryPool&& memoryPool)  = delete;

    pointer allocate(size_t n = 1, const_pointer hint = nullptr);
    void deallocate(pointer p, size_t n = 1);
    template <class U, class... Args> void construct(U* p, Args&&... args);
    template <class U> void destroy(U* p);
private:
    union DATA_ {
        value_type element;
        DATA_* next;
        //stl中union 和下一块的内容指向
    };
    DATA_* currentBlock_;
    DATA_ *  currentSlot_;
    DATA_ *  lastSlot_;
    DATA_ *  freeSlots_;
    void allocateBlock();
};

#endif //MY_REDIES_MEMORYBLOCK_H
