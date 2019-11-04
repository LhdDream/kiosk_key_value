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
bool read_buffer::read_offest(char *data, size_t len) {
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

    //在这里使用一个循环判断处于那个块之中
    size_t  fifter_size = fifter_index.size();
    while(fifter_size != 0)
    {
        //每一个数据块进行匹配
        //找出每一大块的内容多少
        //计算出大小
        //先是fifter
        //如果找到则退出//之后进行数据块的读取
        std::copy(data+len-sizeof(uint32_t) - size*sizeof(uint32_t) - fifter_index[fifter_size],data+len-sizeof(uint32_t) - size*sizeof(uint32_t) - fifter_index[fifter_size- 1 ],fifter_.begin());
        fif_ = std::make_unique<fifter>();
        fif_->SplitString(fifter_);
        if(fif_->match(key_))
        {
            break;
        }
        fifter_size--;
    }
    if(fifter_size)
    {
        //找到
        //给我相应的data块放入解析之中
        std::copy(data+len - sizeof(uint32_t) - size*sizeof(uint32_t) - fifter_index[fifter_index.size() - 1] - data_index[fifter_size],data+len - sizeof(uint32_t) - size*sizeof(uint32_t) - fifter_index[fifter_index.size() - 1] - data_index[fifter_size - 1],buffer_.data());
        return true;
    }
    return false;
}