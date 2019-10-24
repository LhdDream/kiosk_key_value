//
// Created by kiosk on 19-10-18.
//
#include "block_builder.h"
#include <sstream>
block_builder::block_builder() : option_(std::make_unique<options>()),restart_(),cout_(0) {
    offest_.emplace_back(0);
    size_ = 0;
}
void block_builder::Reset() {
    buffer_.clear();
    finished = false;
}

//Entry 定义
void block_builder::Add(sds &key, sds &value) {
    assert(!finished);
    assert(buffer_.empty());
    //这时候记录key的长度或者编码
    //对于key
    //在这里我们使用我们的压缩算法来对key进行压缩，对于value不进行处理
    std::string temp;
    smaz_compress(key.data(),key.size(),&temp);
    buffer_.append(temp);
    buffer_.append("\r\n");
    buffer_.append(value.Tostring());
    buffer_.append("\r\n");
    offest_.emplace_back(buffer_.size());
    size_ ++;
    //将每一对的偏移量放入最前面
}


