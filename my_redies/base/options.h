//
// Created by kiosk on 19-9-12.
//

#ifndef MY_REDIES_OPTIONS_H
#define MY_REDIES_OPTIONS_H

#include <cstddef>

// 在这里设置读写的数据块的压缩方式等
//选项读写的时候
class options
{
public:
    options () : write_buf(8 * 1024 * 1024) , read_buf(4 * 1024 * 1024),block_size(1024 * 64),max_file_size(4 * 1024 * 1024),lru_number(1000000)
    {

    };
    ~options() = default;
    size_t get_lru_number()
    {
        return lru_number;
    }
    size_t  write_()
    {
        return write_buf;
    }
    size_t block_()
    {
        return block_size;
    }
private:
    size_t  write_buf; //  设置写缓冲区的大小
    size_t  read_buf; //  设置读缓冲区的大小
    size_t  block_size; // 设置每一块的内容的大小
                        //在数据库中进行缓存的设置，如果数据量过大
    //Cache * cache; //   每一块的大小进行处理
    size_t max_file_size ;  //在磁盘中存储的文件的大小
    size_t lru_number;//lru_中存储多少条数据
    size_t  key_value_number{};//每多少条Key存储缓冲区之中
    const uint64_t  last_time = 3600; // 每一个小时进行一次合并
};
//read option
struct readoptions{
    //在缓存中进行读取
    readoptions() = default;
    ~readoptions() = default;
    bool cache_read = true;
    //是不是需要存储在本地之中,所读取到的数据
    bool save_local = false;
};
// write option
struct writeoptions{
    bool sync = false; //同步写入操作
};
#endif //MY_REDIES_OPTIONS_H
