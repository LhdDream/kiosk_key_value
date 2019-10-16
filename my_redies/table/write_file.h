//
// Created by kiosk on 19-10-13.
//

#ifndef MY_REDIES_WRITE_FILE_H
#define MY_REDIES_WRITE_FILE_H
//这里使用mmap作为写缓冲区
//为了处理kill -9的情况
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
//只是写入文件
//kvfile 写入文件之中
class  write_file{

public:
    explicit write_file(int seq) : seqnumber(seq),fd(0){
            
    }
    ~write_file() = default;
private:
    int seqnumber  ; //  sst的文件编号
    int fd ; // open 的fd
    std::string buffer;

};
#endif //MY_REDIES_WRITE_FILE_H
