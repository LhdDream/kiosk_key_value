//
// Created by kiosk on 19-10-30.
//

#ifndef MY_SIMPLE_STORAGE_READ_m_bufferH
#define MY_SIMPLE_STORAGE_READ_m_bufferH
//从文件中读取内容
#include <fcntl.h>
#include <cstdint>
#include <sys/mman.h>
#include <sys/stat.h>
#include <memory>
#include "Block.h"
#include "../base/decondig.h"
#include "../config/options.h"
#include "fifter_builder.h"
using namespace deconding;
//使用mmap来进行读取文件中的内容，意图加快读取速率
class read_buffer{
public:
    explicit read_buffer() :m_fif(nullptr),m_block(nullptr),m_iter(nullptr),m_id(options::GetOptions().Id() ),m_key(),m_value(),fd{}{
    }
    bool Read_File();
    bool read_offest(const char * data,size_t len);
    //在每一data块中进行读取
    bool Find_Value(const char * name,int len);
    //读取索引
    void Get_Vector(std::vector<uint32_t > &index,const std::string& off);
    std::string value()
    {
        return m_value;
    }
    void Set_Key(const std::string & key){
        m_key   = key;
    }
    ~read_buffer(){
       close(fd);
    };
private:
    std::unique_ptr<fifter> m_fif; // fif hhh
    std::unique_ptr<Block> m_block;
    std::unique_ptr<Block::Itear> m_iter;
    long long  m_id; // 这个从后往前进行读取，如果没有读取到内容在找之前的数据
    //读取到内容之后不找之前的数据
    std::string m_filename ; // 文件的名称
    std::string m_value; // 读取的值
    std::string m_key ; // 需要寻找的key值
private:
    std::vector<uint32_t > m_data_index; //　每一个数据块的index
    std::vector<uint32_t > m_fifter_index; // index 标记
    std::string m_fifter; // fifter
private:
    std::string m_buffer; // 存储整块的内容
    int fd ;
};
#endif //MY_REDIES_READ_m_bufferH
