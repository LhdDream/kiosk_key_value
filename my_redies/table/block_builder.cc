//
// Created by kiosk on 19-10-18.
//
#include "block_builder.h"
#include <sstream>
block_builder::block_builder() : option_(std::make_unique<options>()),finished(false),fifter_(std::make_unique<fifter>()){

}
void block_builder::Reset() {
    buffer_.clear();
    finished = false;
    offest_.clear();
}
std::string block_builder::finish() {
    char bufs[4];
    for(auto & it : offest_)
    {
        bzero(bufs,sizeof(bufs));
        EncodeInt32(bufs,it);
        buffer_ += bufs;
    }
    bzero(bufs,sizeof(bufs));
    EncodeInt32(bufs,offest_.size());
    buffer_ += bufs;
    finished = true;
    return buffer_;
}
//Entry 定义
void block_builder::Add(const sds &key, const sds &value) {
    assert(!finished);
    //这时候记录key的长度或者编码
    //对于key
    //在这里我们使用我们的压缩算法来对key进行压缩，对于value不进行处理
    offest_.emplace_back(buffer_.size()) ; //对于key_value的偏移量
    std::string temp;
    smaz_compress(key.data(),key.size(),&temp);
    buffer_ += temp;
    buffer_ += '\r';
    std::string p ;
    if(value.size() < 64)
    {
        buffer_ +='0';
        smaz_compress(value.data(),value.size(),&p);
    }else
    {
        buffer_ +='1';
        snappy::Compress(value.data(),value.size() ,&p);
    }
    buffer_ += p;
    buffer_ +=  '\r';
}


