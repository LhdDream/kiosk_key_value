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
#include "../base/options.h"
#include "../util/env.h"
//只是写入文件
//kvfile 写入文件之中
//通过使用顺序写，每次操作直接通过
class  write_file : public  WritableFile{

public:
    explicit write_file(int seq) : seqnumber(seq),fd(0),pos_(0){
            filename =  "." + std::to_string(seqnumber) + "tts";
    }
    ~write_file() override = default;
    bool Append(const sds & data) override {
        //以追加写的方式进行写入
        //拷贝进buffer之中
        const char * write_ = data.data();
        size_t write_size = data.size();
        size_t  avail = (write_size <= (65535-pos_)) ? write_size : (65535-pos_);
        //尽可能写入
        std::memcpy(buf_ + pos_ , write_ , avail) ;
        write_ += avail;
        write_size -= avail; // 复制了多少字节
        pos_ += avail;
        if(write_size == 0 )
        {
            return status::OK();
        }
        //在这里需要判断一下mmap可以完全写入?
        //取最小的
        //在这里缓冲区已经满了，所以需要进行一次写入操作
    }
    bool writeFile(const char * data,size_t size){
        fd = open(filename.c_str(),O_DIRECT | O_CREAT | O_RDWR | O_NOATIME,0666);

        if(ftruncate(fd,size) == -1)
        {
            throw std::bad_exception();
        }
        char * temp = static_cast<char *>(mmap(nullptr,size,PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_POPULATE | MAP_NONBLOCK,fd,0));
        if(memmove(temp,buf_,pos_) == (void *)-1)
        {
            throw std::bad_exception();
        }
        pos_ = 0;
    }
private:
    int seqnumber  ; //  sst的文件编号
    int fd ; // open 的fd
    char buf_[65535]{};
    size_t pos_{}; // 偏移量//mmap的主要偏移量记录
    std::string filename; // 写入的文件内容
};
#endif //MY_REDIES_WRITE_FILE_H
