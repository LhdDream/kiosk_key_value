//
// Created by kiosk on 19-10-23.
//
#include "Block.h"
//这里使用block进行解码等操作
static bool DecondEntry(std::string *p,std::string *key,std::string *value)
{
    // 找出key的长度
    auto it = p->find("\r\n"); // 找出Key的长度
    if(it != -1) {
        std::copy(p->begin(), p->begin() + it, key->begin());
        std::copy(p->begin() + it+ 2,p->end() -2 ,value->end());
        //获取到key和value
        return true;
    }
    else
        return false;
    // 把key放入其中
}

class Block::Itear {
private:
    const char* const data_;
    uint32_t const offest_;  //块中的偏移量开始的地方
    uint32_t const num_offest_;// 有多少个块的偏移量
    uint32_t offest_index_; //读取第几个的key_value
    std::string key_;
    std::string value_;
    std::vector<uint32_t > off_ ; // 表示所有的key_value的键值偏移量
public:

    void readoff_(){
        std::string everyoff_;
        for(size_t i = 0 ; i < num_offest_ ; i++)
        {
            std::copy(data_ + offest_ +  i *4,data_+offest_ + (i+1) *4 ,everyoff_.begin());
            off_.emplace_back(DecodeInt32(everyoff_.data()));
            //获取到每一个key_value 的偏移量
        }
    }
    Itear(const char * data,uint32_t off,uint32_t num):
    data_(data),offest_(off),num_offest_(num),
    offest_index_(num)
    {   readoff_();}
    [[nodiscard]] inline   uint32_t  NextEntryoffest() const {
            return value_.data()  + value_.size() + 2 - data_;
            //找到下一个的指向//得到这个entry的长度大小
    }
    uint32_t  GetoffestPoint(uint32_t index){
        assert(index <= num_offest_);
        //不能够大于它的数量
        assert(index < off_.size());
        return off_[index];
    }
    std::string key() { return key_;}
    sds value() {return value_;}
    bool Seek(const sds &target){
        // 使用二分查找
        uint32_t  left = 0 ;
        uint32_t  right = off_.size() - 1;
        while(left < right)
        {
            uint32_t mid = (left + right + 1) / 2;
            uint32_t  region_off = GetoffestPoint(mid) ;
            //这一位的偏移量
            uint32_t  next_off = GetoffestPoint(mid+1);
            std::string p;
            std::copy(data_ + region_off,data_+ next_off,p);
            DecondEntry(&p,&key_,&value_);
            if(key_ < target.Tostring())
            {
                left = mid;
            }
            else if(key_ == target.Tostring())
            {
                return true;
            }
            else if(key_ > target.Tostring())
            {
                right = mid - 1;
            }
        }
        return false;
    }

};
Block::Itear* Block::newIteratr() {
    if(size_ < sizeof(uint32_t))
    {
        return nullptr;
    }
    const uint32_t  num_offest = numrestarts();
    if(num_offest == 0 )
    {
        return nullptr;
    }
    else {
        return new Itear(data,offest_,num_offest);
    }
}