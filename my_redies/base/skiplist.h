//
// Created by kiosk on 19-9-3.
//

#ifndef MY_REDIES_SKIPLIST_H
#define MY_REDIES_SKIPLIST_H
#include <atomic>
#include <cassert>
#include <cstdlib>
#include "../util/Prena.cc"
#include <boost/any.hpp>
#include <list>
#include <memory>
#include <iostream>
//prene give memory
//skiplist refer to the leveldb
//prena 为内存分配器，尽可能减少内存碎片，防止因为数据过大而导致的内存泄漏
//将一个key 值和一组指针来进行绑定
//进而产生相应的结点

class Prena;
template <typename Key >
class skiplist
{
private:
    struct node{
    Key const key;
    //we can use any
    explicit node(const Key & tmp) : key(tmp),next_(MaxHeight),m(0){
    }
    //this function return n per
    node * next(int n){
        assert(n >= 0) ; // n >= 0  must
        return next_[n];
    }
    void setnext(int n,node *x){
        assert(n >= 0);
        next_[n] = x;
    }
    void setheight(int x){
        m = x;
    }
    int  getheight(){
        return m;
    }
    void clear()
    {
        next_.clear();
        m = 0;
    }
    ~node(){
    }
private:
    std::vector<node *> next_;
    int m;
    //多个指针的集合
    //在这里并没有使用原子操作 // 目前打算实现的是单线程模式
    }; // skiplist  node
public:
    explicit  skiplist(Prena * prena);
    skiplist(const skiplist&) = delete;
    skiplist&operator=(const skiplist&) = delete;
    ~skiplist(){
        delete prena_;
        delete head_;
    }
    //insert key into the list
    void Insert(const Key & key);
    //turn the key is in  the list
    bool Delete(const Key & key);
    node * find(const Key & key) const;
    //iteration over a skip list

private:
    enum {MaxHeight = 8};
    Prena *prena_;
    node * head_;
    std::atomic<int> max_height_;
    //this file construct two-way link list
    //we are running this
private:
    [[nodiscard]] inline int GetMaxheight() const
    {
        return max_height_.load(std::memory_order_relaxed);
    }
    //被修饰的函数返回值十分重要，或者美剧类型，对象类型时分重要不能被废弃
    bool Equal(const Key &a , const Key &b) { return a == b ;}
    node * Findlessthan(const Key & key,node ** prev) const ;// 找到比这个key小的上一个元素
    //return the last element
    node *newnode(const Key& key,int height);

};
#endif //MY_REDIES_SKIPLIST_H
