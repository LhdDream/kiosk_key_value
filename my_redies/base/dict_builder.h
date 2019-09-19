//
// Created by kiosk on 19-9-15.
//

#ifndef MY_REDIES_DICT_BUILDER_H
#define MY_REDIES_DICT_BUILDER_H

#include "../util/parallel_hashmap/phmap.h"
#include <any>
#include "sds.h"
#include <memory>
#include "deconding.h"
#include "options.h"
#include "skiplist.h"
#include "../util/bloom_filter.h"
using phmap::parallel_flat_hash_map;
//在这里使用内存表的构建
//内存表主要是通过pashmap来进行构建，同时提供多线程并发访问
class options;

template  <typename  T>
class dict
{
public:
        explicit dict() : ht_(std::make_unique<parallel_flat_hash_map<sds,type>>()),
        type__(std::make_unique<std::vector<type>>),
         options_(std::make_unique<options>()),
         bloom_(std::make_unique<bloom<sds>>()){
        }
        dict(const dict & ) = delete ;
        dict operator = (const dict &) = delete;
        ~dict() = default;
        bool Add(sds& , T&) ; // 封装的add
        //引用只能被初始化一次
        bool Get(sds&,sds *);// 查找
private:
    typedef struct type{
        sds type_ = "-1"; // -1的话标志已经被删除,其余均为正常
        sds value_ ;
    }type; // 存储类型和type 在add之后维护的map之中如此使用get的时候
    //根据type 来进行反解压
    std::unique_ptr< parallel_flat_hash_map<sds,std::any> >ht_;
    std::unique_ptr<std::vector<type>> type__;
    std::unique_ptr<options> options_;
    std::unique_ptr<bloom<sds>> bloom_;//bloom 过滤器
};
#endif //MY_REDIES_DICT_BUILDER_H
