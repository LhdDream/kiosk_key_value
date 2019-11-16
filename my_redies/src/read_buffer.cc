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
    std::vector<char>temp;
    for(size_t i = 0 ; i < off.size()/4 ; i++)
    {
        temp.resize(4);
        std::copy(off.begin() +  i *4 , off.begin() + (i+1) *4 ,temp.begin());
        index.emplace_back(DecodeInt32(temp.data()));
    }
}
bool read_buffer::read_offest(const char *data, size_t len) {
    uint32_t size = DecodeInt32(data+len-sizeof(uint32_t));
    //得到所有偏移量的长度
    std::string altogether ;
    altogether.resize(size * sizeof(uint32_t));
    std::copy(data+len-sizeof(uint32_t) - size*sizeof(uint32_t) - 2,data+len-sizeof(uint32_t),altogether.begin());
    auto it = altogether.find('\r');
    std::string temp1 , temp2;
    temp1.resize(it);
    temp2.resize(altogether.end() - altogether.begin()  - it);
    std::copy(altogether.begin(),altogether.begin()+it,temp1.begin());
    std::copy(altogether.begin()+it+1,altogether.end(),temp2.begin());
    get_vector(data_index,temp1);
    get_vector(fifter_index,temp2);
    //先data块后fifter块
    //在这里使用一个循环判断处于那个块之中
    size_t  fifter_size = 0;
    size_t  index_fif = fifter_index.size() - 1;
    while(fifter_size <= index_fif)
    {
        //每一个数据块进行匹配
        //找出每一大块的内容多少
        //计算出大小
        //先是fifter
        //如果找到则退出//之后进行数据块的读取
        fifter_.resize(fifter_index[fifter_size + 1] - fifter_index[fifter_size]);
        std::copy(data+len-(size + 1) * sizeof(uint32_t)  - 2 - fifter_index[index_fif] + fifter_index[fifter_size],data+len-(size + 1) * sizeof(uint32_t) - 2 - fifter_index[index_fif ] + fifter_index[fifter_size + 1],fifter_.begin());
        fif_ = std::make_unique<fifter>();
        fif_->SplitString(fifter_);
        if(fif_->match(key_))
        {
            break;
        }
        fifter_size++;
    }
    if(fifter_size  <= index_fif)
    {
        //找到
        //给我相应的data块放入解析之中
        buffer_.resize(data_index[fifter_size + 1]-data_index[fifter_size]);
        std::copy(data+len - (size +1 ) *sizeof(uint32_t) - fifter_index[index_fif] - data_index[data_index.size() - 1] - 2 + data_index[fifter_size],data+len - 2 - (size + 1)*sizeof(uint32_t) - fifter_index[index_fif] - data_index[data_index.size() - 1] + data_index[fifter_size + 1],buffer_.begin());
        // 0 -12412tatic_cast
        //
        return true;
    }
    return false;
}
bool read_buffer::read_file() {
        int len = 0;
        while(id == 0)
        {
            file_name = "." +std::to_string(id) +"tts";
            fd = open(file_name.c_str(),O_RDONLY | O_CLOEXEC | O_DIRECT,0666);
            if(fd == -1) // 文件不存在
            {
                id--;//查看下一个文件是不是存在
                continue;
            }
            struct stat st{};
            auto r = fstat(fd,&st);
            if(r == -1)
            {
                close(fd);
                return  false;
            }
            len = st.st_size;
            auto re_buffer = reinterpret_cast<char *> (mmap(nullptr,len,PROT_READ ,
                                                   MAP_SHARED | MAP_POPULATE | MAP_NONBLOCK,fd,0));
            if(re_buffer == nullptr) {
                return false;
            }
            std::string sim_buffer(re_buffer,len); // 转化为buffer

            snappy::Uncompress(sim_buffer.data(),sim_buffer.size(),&real_buffer_);
            if(!read_offest(real_buffer_.data(),real_buffer_.size()))
            {
                break;
            }
            block_ = std::make_unique<Block>(buffer_);
            if(find_value())
            {
                id = option_->get_id();
                break;
            }
            id--;
        }
        block_.release(); // 对象生命周期的问题
        real_buffer_.clear();
        return id == option_->get_id();
}