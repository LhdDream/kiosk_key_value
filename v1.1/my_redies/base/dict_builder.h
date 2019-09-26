//
// Created by kiosk on 19-9-15.
//

#ifndef MY_REDIES_DICT_BUILDER_H
#define MY_REDIES_DICT_BUILDER_H

#include "../util/parallel_hashmap/phmap.h"
#include <any>
#include "sds.h"
#include <memory>
#include "options.h"
#include "skiplist.h"
#include "../util/bloom_filter.h"
#include "../util/parallel_hashmap/phmap_utils.h"
using phmap::parallel_flat_hash_map;
//在这里使用内存表的构建
//内存表主要是通过pashmap来进行构建，同时提供多线程并发访问
class options;

struct sdsHash{
    size_t operator()(const sds & rhs) const{
     return phmap::HashState().combine(0,rhs.data());
    }
};
class dict
{
public:
        explicit dict() : ht_(std::make_unique<parallel_flat_hash_map<sds,sds,HashFunc,EqualKey>>()),
         options_(std::make_unique<options>()),
         bloom_(std::make_unique<bloom>()){
        }
        dict(const dict & ) = delete ;
        dict operator = (const dict &) = delete;
        ~dict() = default;
        void Add(const sds& ,const  sds &) ; // 封装的add
        //引用只能被初始化一次
        bool Get(const sds&,std::string *);// 查找
        bool Delete(const sds&);
private:
    //根据type 来进行反解压
    std::unique_ptr< parallel_flat_hash_map<sds,sds,HashFunc,EqualKey> >ht_;
    std::unique_ptr<options> options_;
    std::unique_ptr<bloom> bloom_;//bloom 过滤器
    std::string buffer ; // snappy 的buffer，防止生命周期提前被释放
};
#endif //MY_REDIES_DICT_BUILDER_H
