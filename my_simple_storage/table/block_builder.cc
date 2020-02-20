//
// Created by kiosk on 19-10-18.
//
#include "block_builder.h"
#include <sstream>

void block_builder::Reset() {
    m_finished = false;
    m_buffer.clear();
    m_offset.clear();
}

std::string block_builder::Finish() {
    std::string temp;
    for (const auto &it :m_buffer) {
        temp += it;
    }
    char bufs[4];
    for (auto &it : m_offset) {
        bzero(bufs, sizeof(bufs));
        EncodeInt32(bufs, it);
        temp.append(bufs, sizeof(bufs));
    }
    bzero(bufs, sizeof(bufs));
    EncodeInt32(bufs, m_offset.size());
    temp.append(bufs, sizeof(bufs));
    m_finished = true;
    return temp;
}

//Entry 定义
void block_builder::Add(const std::string &key, const std::string &value) {
    std::string buffer;
    m_fifter->Add(key);
    buffer = key;
    buffer = '\r' + buffer + '\r';
    buffer += value;
    m_buffer.emplace_back(buffer);
    m_offset.emplace_back(buffer.size()); //对于key_value的偏移量
}


