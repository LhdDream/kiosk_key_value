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
    [[nodiscard]] inline size_t Current() const {
        return (buffer_.size() + restart_.size() * sizeof(uint32_t) + sizeof(uint32_t));
    };
    std::string finish() ;
    ~block_builder() = default;
private:
    std::unique_ptr<options> option_;
    std::string buffer_;
    std::vector<uint32_t > restart_ ; //重启点的偏移量
    int cout_ ;
    bool finished{}; // 写入完成
};
#endif //MY_REDIES_BLOCK_BUILDER_H
