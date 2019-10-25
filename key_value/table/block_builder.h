//
// Created by kiosk on 19-10-17.
//

#ifndef MY_REDIES_BLOCK_BUILDER_H
#define MY_REDIES_BLOCK_BUILDER_H
 // 组织块的大小
#include <cstdint>
#include <vector>
#include "../base/sds.h"
 // 组织数据块中的内容
class block_builder{
public:
    block_builder(const block_builder &) = delete;
    block_builder&operator=(const block_builder &) = delete;
    void  Add(sds & key,sds & value); 
private:

};
#endif //MY_REDIES_BLOCK_BUILDER_H
