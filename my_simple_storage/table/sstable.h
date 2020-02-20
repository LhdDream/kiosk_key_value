//
// Created by kiosk on 19-10-1.
//

#ifndef MY_SIMPLE_STORAGE__SSTABLE_H
#define MY_SIMPLE_STORAGE__SSTABLE_H

#include <snappy.h>

#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../util/bloom_filter.h"
#include "../util/memorypool/memorypool.h"
#include "block_builder.h"
#include "read_buffer.h"
#include "write_file.h"

using namespace deconding;

//总目录
//静态索引一层，数据一层
//先进行顺序读取
//索引加具体内容
//总索引
// data m_block = restart
//思路，先读取所有的整个索引
//首先把然后通过判断每一个索引块来进行编写

class sstable {
public:
    explicit sstable()
        : m_read(std::make_unique<read_buffer>()),
          m_write(nullptr),
          m_block(std::make_unique<block_builder>()) {
        m_data_index.emplace_back(0);
        m_fifter_index.emplace_back(0);
    }

    void UnmemtableAdd(
        const std::map<std::string, std::string, std::less<>, MemoryPool<std::pair<std::string, std::string>>>& value);

    bool Get(const std::string& key_, std::string& value);

    //每一个数据块的偏移量
    void Offset(std::vector<uint32_t>& index);

    void Write_NameFile();

    void Reset();

private:
    std::unique_ptr<read_buffer> m_read;
    std::unique_ptr<write_file> m_write;
    std::unique_ptr<block_builder> m_block;
    // 转化为有序的map进行存储
    std::string m_buffer;                  // 写入文件的内容
    std::string m_offset;                  //偏移量的offest
    std::string m_fifter_buffer;           // fifter 中的buffer
    std::vector<uint32_t> m_data_index;    //　每一个数据块的index
    std::vector<uint32_t> m_fifter_index;  // index 标记
};

#endif
