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
    options () : write_buf(8 * 1024 * 1024) , read_buf(4 * 1024 * 1024),block_size(8192),max_file_size(4 * 1024 * 1024)
    {

    };
private:
    size_t write_buf; //  设置写缓冲区的大小
    size_t  read_buf; //  设置读缓冲区的大小
    size_t  block_size; // 设置每一块的内容的大小
                        //在数据库中进行缓存的设置，如果数据量过大
    //Cache * cache; //   每一块的大小进行处理
    size_t max_file_size ;  //在磁盘中存储的文件的大小
    // 这里使用Ｇｏｏｇｌｅ的snappy 来进行压缩,尽可能的在单核的情况下跑满
    //同时存储的命令也使用snappy进行压缩
    //通过什么顺序来进行排序
    // Compear * compearotr
    // size_t db_size ; //  默认创建几个数据库，采用单线程的方式但是可以采用多个数据库来进行
    //　数据的迁移操作
    // 悲观锁和乐观锁
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
