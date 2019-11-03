//
// Created by kiosk on 19-11-3.
//
#include "read_buffer.h"
bool read_buffer::find_value() {
    Iter_.reset(block_->newIteratr());
    if(Iter_->Seek(key_))
    {
        value_ =  Iter_->value();
        return true;
    }
    return false;
}
void read_buffer::get_vector(std::vector<uint32_t> &index, const std::string &off) {
    std::string temp;
    for(size_t i = 0 ; i < off.size()/4 ;i++)
    {
        std::copy(off.begin() +  i *4,off.begin() + (i+1) *4 ,temp.begin());
        index.emplace_back(DecodeInt32(temp.data()));
        temp.clear();
    }
}
void read_buffer::read_offest(char *data, size_t len) {
    uint32_t size = DecodeInt32(data+len-sizeof(uint32_t));
    //得到所有偏移量的长度
    std::string altogether ;
    std::copy(data+len-sizeof(uint32_t) - size*sizeof(uint32_t),data+len-sizeof(uint32_t),altogether.begin());
    auto it = altogether.find('\r');
    std::string temp1 , temp2;
    std::copy(altogether.begin(),altogether.begin()+it,temp1.begin());
    std::copy(altogether.begin()+it+2,altogether.end(),temp2.begin());
    get_vector(fifter_index,temp1);
    get_vector(data_index,temp2);
}