//
// Created by kiosk on 19-10-23.
//
#include "Block.h"
//这里使用block进行解码等操作
static bool DecondEntry(std::string &p,std::string &key,std::string &value)
{
        auto it = p.find('\r');
        if(it == -1){
           return false;
        }
        auto it1 = p.find('\r', it + 1);
        if(it1 == -1){
            return false;
        }
        std::string temp;
        temp = p.substr(it + 1, it1 - 1);
        key = temp;
        temp = p.substr(it1 + 1, p.size());
        value = temp;
    return true;
}

bool Block::Itear::Seek(const std::string &target) {
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
            p.resize(next_off - region_off);
            std::copy(data_ + region_off,data_+ next_off,p.begin());
            DecondEntry(p,key_,value_);
            if(key_ < target)
            {
                left = mid;
            }
            else if(key_ == target)
            {
                return true;
            }
            else if(key_ > target)
            {
                right = mid - 1;
            }
        }
        return false;

}

std::unique_ptr<Block::Itear> Block::newItear(const char * data_,int len) {
        m_offest = len  - (  DecodeInt32(data_+len - sizeof(uint32_t))) * sizeof(uint32_t) -
                sizeof(uint32_t);
        auto m_iter = std::make_unique<Itear>(data_,m_offest,DecodeInt32(data_+len - sizeof(uint32_t)));
        return m_iter;
}