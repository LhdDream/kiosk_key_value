//
// Created by kiosk on 19-9-12.
//

#ifndef MY_REDIES_OPTIONS_H
#define MY_REDIES_OPTIONS_H

#include <cstddef>
#include "sds.h"
// 在这里设置读写的数据块的压缩方式等
//选项读写的时候
class options
{
public:
    options () : write_buf( 64 * 1024) , read_buf(4 * 1024 * 1024),block_size(1024 * 8 ),max_file_size(4 * 1024 * 1024),lru_number(1024000),id_(0)
    {
    };
    ~options() = default;
    inline size_t get_lru_number()
    {
        return lru_number;
    }
    inline size_t  write_()
    {
        return write_buf;
    }
    inline size_t block_()
    {
        return block_size;
    }
    inline long long get_id()
    {
        return id_;
    }
    void makefilename(std::string *filename){
        *filename = "."+std::to_string(id_) + "tts";
        id_++;
    }
private:
    size_t  write_buf; //  设置写缓冲区的大小
    size_t  read_buf; //  设置读缓冲区的大小
    size_t  block_size; // 设置每一块的内容的大小
                        //在数据库中进行缓存的设置，如果数据量过大
    //Cache * cache; //   每一块的大小进行处理
    size_t max_file_size ;  //在磁盘中存储的文件的大小
    size_t lru_number;//lru_中存储多少条数据
    const size_t  number_ = 4;//sstable 0
    const size_t  last_time = 3600; // 每一个小时进行一次合并
    long long id_ ; // sstable的id
};

struct c
{
    bool operator()(const sds &x ,const sds &y) const {
        return x.Tostring() < y.Tostring();
    }
};
#endif //MY_REDIES_OPTIONS_H
