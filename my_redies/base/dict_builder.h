//
// Created by kiosk on 19-9-15.
//

#ifndef MY_REDIES_DICT_BUILDER_H
#define MY_REDIES_DICT_BUILDER_H
#include <deque>
#include <queue>
#include <algorithm>
#include <any>
#include "sds.h"
#include <memory>
#include "options.h"
#include "skiplist.h"
#include "../table/sstable.h"
#include "../table/sstable.cc"
#include <map>
//在这里使用内存表的构建
//内存表主要是通过pashmap来进行构建，同时提供多线程并发访问
class options;

//在这里实现lru 策略
//设置过时时间淘汰相应的键
//lfu 暂时不进行考虑
//lru 在所有的key中找出一部分，找出距离现在距离最迟的key,并且进行淘汰
//根据超时时间来进行
//记录一下每一个元素的访问时间


class dict
{
public:
        explicit dict() : ht_(std::make_unique<std::map<sds,sds>>()),
         options_(std::make_unique<options>()),
         list_(std::make_unique<std::list< sds >>()),
         bloom_(std::make_shared<bloom>()),
         buffer_size(0),
         sstable_(std::make_unique<sstable>()){
        }
        dict(const dict & ) = delete ;
        dict operator = (const dict &) = delete;
        ~dict() = default;
        void Add(const sds& ,const  sds &) ; // 封装的add
        //引用只能被初始化一次
        bool Get(const sds&,std::string *);// 查找
        bool Delete(const sds&);

        void PDelete();//被动淘汰
        void Put(const sds &);

private:
    //根据type 来进行反解压
    std::unique_ptr<std::map<sds,sds> >ht_;
    std::unique_ptr<options> options_;
    std::string buffer ; // snappy 的buffer，防止生命周期提前被释放
    std::unique_ptr<std::list<sds>> list_;
    //  维护的链表
    //双线链表维护的缓存内容的使用顺序
    //在一定时间内进行删除
    //主动淘汰和被动淘汰
    //每次进行内存的写入的时候，可以直接进行内存的释放
    std::shared_ptr<bloom> bloom_;//bloom 过滤器

    unsigned long long buffer_size ;
    std::unique_ptr<sstable> sstable_; // sstable
};
#endif //MY_REDIES_DICT_BUILDER_H
