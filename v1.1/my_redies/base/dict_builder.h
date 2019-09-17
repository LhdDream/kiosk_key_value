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
#include "options.h"
using phmap::parallel_flat_hash_map;
using phmap::parallel_flat_hash_set;
class options;
template  <typename  T>
class dict
{
public:
        explicit dict() : ht_(std::make_unique<parallel_flat_hash_map<sds,type>>()),
        type__(std::make_unique<std::vector<type>>),
         options_(std::make_unique<options>()){
        }
        ~dict() = default;
        bool Add(sds& , T&) ; // 封装的add
private:
    typedef struct type{
        std::string type_;
        std::string value_ = "-1";
    }type; // 存储类型和type 在add之后维护的map之中如此使用get的时候
    //根据type 来进行反解压
    std::unique_ptr< parallel_flat_hash_map<sds,type> >ht_;
    std::unique_ptr<std::vector<type>> type__;
    std::unique_ptr<options> options_;
};
#endif //MY_REDIES_DICT_BUILDER_H
