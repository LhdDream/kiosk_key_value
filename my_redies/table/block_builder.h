//
// Created by kiosk on 19-10-17.
//

#ifndef MY_REDIES_BLOCK_BUILDER_H
#define MY_REDIES_BLOCK_BUILDER_H
 // 组织块的大小
#include <cstdint>
#include <vector>
#include "../base/sds.h"
#include "../base/options.h"
#include "../base/decondig.h"
#include "../base/decondig.cc"
using namespace deconding;
 // 组织数据块中的内容
class block_builder{
public:
    block_builder();
    block_builder(const block_builder &) = delete;
    block_builder&operator=(const block_builder &) = delete;
    void  Add(sds & key,sds & value);
    [[nodiscard]] bool empty() const { return buffer_.empty();}
    void Reset();

    ~block_builder() = default;
    std::string finish();
    [[nodiscard]] inline size_t  buffer_size() const {
        return  buffer_.size();
    }
private:
    std::unique_ptr<options> option_;
    std::string buffer_;
    bool finished{}; // 写入完成
    long long size_; // 记录一块中有多少个key_value 对
    std::vector<uint32_t > offest_; // 每一recode的偏移量
    //写到每一块的最后面
};
#endif //MY_REDIES_BLOCK_BUILDER_H
