//
// Created by kiosk on 19-10-17.
//

#ifndef MY_REDIES_BLOCK_H
#define MY_REDIES_BLOCK_H
//sstable 中所构建的数据块
#include <unistd.h>
#include <cstdint>
#include "../base/sds.h"
#include "../base/decondig.h"
using namespace deconding;
// 每一个数据块中的最后维护
class Block{
public:
    explicit Block(const sds & data_) : data(data_.data()),size_(data_.size()){
        if(size_ < sizeof(uint32_t))
        {
            size_ = 0 ;//出现错误
        }
        else{
             offest_ = size_ - (1 + numrestarts() * sizeof(uint32_t));
             //块中的offest的偏移量
        }
    }
    [[nodiscard]] size_t  size() const {
        return size_;
    }
    ~Block(){
        delete  [] data;
    }
    [[nodiscard]] uint32_t numrestarts() const {
        return DecodeInt32(data + size_ - sizeof(uint32_t));
    }; //返回offest 的个数
    class Itear;
    Itear * newIteratr();
private:
    const char * data;
    size_t size_;
    uint32_t  offest_  ;// offest 的刚开始的地方
};

class Block::Itear {
private:
    const char* const data_;
    uint32_t const offest_;  //块中的偏移量开始的地方
    uint32_t const num_offest_;// 有多少个块的偏移量
    uint32_t offest_index_; //读取第几个的key_value
    std::string key_;
    std::string value_;
    std::vector<uint32_t > off_ ; // 表示所有的key_value的键值偏移量
private:
    void readoff_(){
        std::string everyoff_;
        for(size_t i = 0 ; i < num_offest_ ; i++)
        {
            std::copy(data_ + offest_ +  i *4,data_+offest_ + (i+1) *4 ,everyoff_.begin());
            off_.emplace_back(DecodeInt32(everyoff_.data()));
            //获取到每一个key_value 的偏移量
            everyoff_.clear();
        }
    }

public:
    Itear(const char * data,uint32_t off,uint32_t num):
            data_(data),offest_(off),num_offest_(num),
            offest_index_(num)
    {   readoff_();}

private:

    uint32_t  GetoffestPoint(uint32_t index){
        assert(index <= num_offest_);
        //不能够大于它的数量
        assert(index < off_.size());
        return off_[index];
    }

public:
    std::string key() { return key_;}
    sds value() {return value_;}
    bool Seek(const sds &target);

};
#endif //MY_REDIES_BLOCK_H
