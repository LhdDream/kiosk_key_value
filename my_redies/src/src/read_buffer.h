//
// Created by kiosk on 19-10-30.
//

#ifndef MY_REDIES_READ_BUFFER_H
#define MY_REDIES_READ_BUFFER_H
//从文件中读取内容
#include <fcntl.h>
#include <cstdint>
#include <sys/mman.h>
#include <sys/stat.h>
#include <memory>
#include "../table/Block.h"
#include "../base/decondig.h"
#include "../base/options.h"
#include "../base/sds.h"
#include "../table/fifter_builder.h"
using namespace deconding;
//使用mmap来进行读取文件中的内容，意图加快读取速率
class read_buffer{
public:
    explicit read_buffer(std::shared_ptr<options> &op,sds &key) :fif_(nullptr),block_(nullptr),Iter_(nullptr),option_(op),id(option_->get_id()),re_buffer(nullptr),key_(key){
    }
    bool read_file()
    {
            while(id == 0)
            {
                file_name = "." +std::to_string(id) +"tts";
                auto fd = open(file_name.c_str(),O_RDONLY | O_CLOEXEC,0666);
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
                int len = st.st_size;
                re_buffer = static_cast<char *>  (mmap(nullptr,len,PROT_READ ,
                                                       MAP_SHARED | MAP_POPULATE | MAP_NONBLOCK,fd,0));
                if(re_buffer == nullptr) {
                    return false;
                }
                if(read_offest(re_buffer,len))
                {
                    break;
                }
                block_ = std::make_unique<Block>(re_buffer);
                if(find_value())
                {
                    id = option_->get_id();
                    break;
                }
                id--;
            }
            return id == option_->get_id();
    }
    //在每一data块中进行读取
    bool find_value();
    //读取索引
    bool read_offest(char * data,size_t len);
    void get_vector(std::vector<uint32_t > &index,const std::string& off);

private:
    std::unique_ptr<fifter> fif_; // fif hhh
    std::unique_ptr<Block> block_;
    std::unique_ptr<Block::Itear> Iter_;
    std::shared_ptr<options> option_;
    long long  id; // 这个从后往前进行读取，如果没有读取到内容在找之前的数据
    //读取到内容之后不找之前的数据
    char * re_buffer; // 读取的buffer
    std::string file_name ; // 文件的名称
    sds value_; // 读取的值
    sds key_ ; // 需要寻找的key值
private:
    std::vector<uint32_t > data_index; //　每一个数据块的index
    std::vector<uint32_t > fifter_index; // index 标记
    std::string fifter_; // fifter
private:
    sds buffer_; // 存储整块的内容
};
#endif //MY_REDIES_READ_BUFFER_H
