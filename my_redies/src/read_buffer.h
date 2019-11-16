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
    explicit read_buffer(std::shared_ptr<options> &op,sds &key) :fif_(nullptr),block_(nullptr),Iter_(nullptr),option_(op),id(op->get_id()),key_(key),fd{}{
    }
    bool read_file();
    bool read_offest(const char * data,size_t len);
    //在每一data块中进行读取
    bool find_value();
    //读取索引
    void get_vector(std::vector<uint32_t > &index,const std::string& off);
    std::string value()
    {
        return value_.Tostring();
    }
    ~read_buffer(){
       close(fd);
    };
private:
    std::unique_ptr<fifter> fif_; // fif hhh
    std::unique_ptr<Block> block_;
    std::unique_ptr<Block::Itear> Iter_;
    std::shared_ptr<options> option_;
    long long  id; // 这个从后往前进行读取，如果没有读取到内容在找之前的数据
    //读取到内容之后不找之前的数据
    std::string file_name ; // 文件的名称
    sds value_; // 读取的值
    sds key_ ; // 需要寻找的key值
private:
    std::vector<uint32_t > data_index; //　每一个数据块的index
    std::vector<uint32_t > fifter_index; // index 标记
    std::string fifter_; // fifter
private:
    std::string buffer_; // 存储整块的内容
    std::string real_buffer_; // 从mmap读取的内容并且解压
    int fd ;
};
#endif //MY_REDIES_READ_BUFFER_H
