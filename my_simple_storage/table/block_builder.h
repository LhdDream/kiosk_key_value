//
// Created by kiosk on 19-10-17.
//

#ifndef MY_SIMPLE_STORAGE_BLOCK_BUILDER_H
#define MY_SIMPLE_STORAGE_BLOCK_BUILDER_H
// 组织块的大小
#include <memory>
#include <cstdint>
#include <vector>
#include "../config/options.h"
#include "../base/decondig.h"
#include "fifter_builder.h"
#include <snappy.h>

using namespace deconding;

// 组织数据块中的内容
class block_builder {
public:
    block_builder() : m_finished(false), m_fifter(std::make_unique<fifter>()) {
    }

    ~block_builder() = default;

    block_builder(const block_builder &) = delete;

    block_builder &operator=(const block_builder &) = delete;

    void Add(const std::string &key, const std::string &value);

    void Reset();

    std::string Finish();

    size_t Buffer_Size() const {
        return m_buffer.size() + (m_offset.size() * 4);
    }

    std::string To_Fif() const {
        return m_fifter->To_string(); // 表示转化
    }

private:
    bool m_finished; // 写入完成
    std::unique_ptr<fifter> m_fifter; // 对于每一块的fifter 过滤器
    std::vector<std::string> m_buffer; // 一整块的内容
    std::vector<uint32_t> m_offset;
};

#endif //MY_REDIES_BLOCK_BUILDER_H
