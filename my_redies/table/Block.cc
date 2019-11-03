//
// Created by kiosk on 19-10-23.
//
#include "Block.h"
//这里使用block进行解码等操作
static bool DecondEntry(std::string *p,std::string *key,std::string *value)
{
    // 找出key的长度
    auto it = p->find('\r'); // 找出Key的长度
    if(it != -1) {
        std::string key_;
        std::copy(p->begin(), p->begin() + it , key_.begin());
        smaz_decompress(key_.data(),key_.size(),key);
        auto  type = p->at(it +2);
        std::string value_;
        std::copy(p->begin() + it+ 3,p->end() -2 ,value_.begin());
        if(type == '0')
        {
            smaz_decompress(value_.data(),value_.size(),value);
        }
        snappy::Uncompress(value_.data(),value_.size(),value);
        //获取到key和value
        return true;
    }
    else
        return false;
    // 把key放入其中
}

bool Block::Itear::Seek(const sds &target) {
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
            std::copy(data_ + region_off,data_+ next_off,p.begin());
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