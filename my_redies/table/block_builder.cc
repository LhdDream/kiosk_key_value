//
// Created by kiosk on 19-10-18.
//
#include "block_builder.h"
block_builder::block_builder() : option_(std::make_unique<options>()),restart_(),cout_(0) {
    restart_.emplace_back(0); // 重启点的第一位设置为
}
void block_builder::Reset() {
    restart_.clear();
    restart_.emplace_back(0);
    buffer_.clear();
    cout_ = 0;
    finished = false;
}
std::string block_builder::finish() {
    //把重启点进行编码压缩
    for(auto & it : restart_)
    {
       char bufs[sizeof(it)];
       EncodeInt32(bufs,it);
       buffer_.append(bufs,sizeof(bufs));
    }
    char bufs[sizeof(restart_.size())];
    EncodeInt32(bufs,restart_.size());
    buffer_.append(bufs,sizeof(bufs));
    finished = true;
    return buffer_;
}
void block_builder::Add(sds &key, sds &value) {
    assert(!finished);
    assert(buffer_.empty());
    //这时候记录key的长度或者编码
    //对于key和value 进行压缩
}