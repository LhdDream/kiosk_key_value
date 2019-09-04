//
// Created by kiosk on 19-9-3.
//

#ifndef MY_REDIES_SKIPLIST_H
#define MY_REDIES_SKIPLIST_H
#include <atomic>
#include <cassert>
#include <cstdlib>
#include "../util/Prena.h"
#include <boost/any.hpp>
#include <list>
#include <memory>
//prene give memory
//skiplist
class Prena;
template <typename Key , class com>
        //class class type typename 基础类型
class skiplist
{
public:
    explicit  skiplist(com cmp , Prena * prena);
    skiplist(const skiplist&) = delete;
    skiplist&operator=(const skiplist&) = delete;
    //insert key into the list
    void Insert(const Key & key);
    //turn the key is in  the list
    bool find(const Key & key) const;
    //iteration over a skip list
    class Iterator{
    public:
    private:
    };
private:
    struct node; // skiplist  node
    enum {MaxHeight = 12};
    std::unique_ptr<Prena> prena_;
    std::unique_ptr<node> head_;
    std::atomic<int> max_height_;
};

#endif //MY_REDIES_SKIPLIST_H
