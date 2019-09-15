//
// Created by kiosk on 19-9-15.
//

#ifndef MY_REDIES_DICT_BUILDER_H
#define MY_REDIES_DICT_BUILDER_H
//这里进行构建每一块之中的内容
//进行hash表的构建
#include "../util/parallel_hashmap/phmap.h"
#include <any>
#include "sds.h"
#include <memory>
#include "deconding.h"
using phmap::parallel_flat_hash_map;
template  <typename  T>
class dict
{
public:
        explicit dict() : ht_(std::make_unique<parallel_flat_hash_map<sds,type>>())
        {
        }
        ~dict() = default;
        bool Add(sds& , T&) ; // 封装的add
        bool Delete(sds &); //封装的delete
private:
    typedef struct type{
        std::string type_;
        std::string value_;
    }type; // 存储类型和type 在add之后维护的map之中如此使用get的时候
    //根据type 来进行反解压
    std::unique_ptr< parallel_flat_hash_map<sds,type> >ht_;
};
#endif //MY_REDIES_DICT_BUILDER_H
