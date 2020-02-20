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
        uint32_t  right = m_off.size() - 1;
        while(left < right)
        {
            uint32_t mid = (left + right + 1) / 2;
            uint32_t  region_off = GetoffsetPoint(mid) ;
            //这一位的偏移量
            uint32_t  next_off = GetoffsetPoint(mid+1);
            std::string p;
            p.resize(next_off - region_off);
            std::copy(m_data + region_off,m_data+ next_off,p.begin());
            DecondEntry(p,m_key,m_value);
            if(m_key < target)
            {
                left = mid;
            }
            else if(m_key == target)
            {
                return true;
            }
            else if(m_key > target)
            {
                right = mid - 1;
            }
        }
        return false;

}

std::unique_ptr<Block::Itear> Block::newItear(const char * data_,int len) {
        m_offset = len  - (  DecodeInt32(data_+len - sizeof(uint32_t))) * sizeof(uint32_t) -
                sizeof(uint32_t);
        auto m_iter = std::make_unique<Itear>(data_,m_offset,DecodeInt32(data_+len - sizeof(uint32_t)));
        return m_iter;
}
void Block::Itear::ReadOff() {
        std::string everyoff_;
        uint32_t number = 0 ;
        m_off.emplace_back(number);
        for(size_t i = 0 ; i < m_num_offset ; i++)
        {
            everyoff_.resize(5,'\0');
            std::copy(m_data + m_offset +  i *4,m_data + m_offset + (i+1) *4 ,everyoff_.begin());
            number += DecodeInt32(everyoff_.data());
            m_off.emplace_back(number);
            //获取到每一个key_value 的偏移量
        }
}