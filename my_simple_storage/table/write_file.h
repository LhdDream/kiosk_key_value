//
// Created by kiosk on 19-10-13.
//

#ifndef MY_SIMPLE_STORAGE_WRITE_FILE_H
#define MY_SIMPLE_STORAGE_WRITE_FILE_H
//这里使用mmap作为写缓冲区
//为了处理kill -9的情况
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../config/options.h"
#include <cerrno>

//只是写入文件
//kvfile 写入文件之中
//通过使用顺序写，每次操作直接通过
class  write_file{

public:
    explicit write_file(std::string &&name) : filename(std::move(name)),fd(0){
    }
    ~write_file()  = default;
    write_file(const write_file &) = delete;
    write_file operator = (const write_file &&) = delete;
    write_file operator = (const write_file & ) = delete;
    bool writeFile(const char * data_,size_t size){
        try{
            fd = open(filename.c_str(),O_DIRECT | O_CREAT | O_RDWR | O_NOATIME | O_APPEND,0666);
        //O_DIRECT 直接与磁盘进行IO操作
             if(fd < 0 )
             {
                 throw std::invalid_argument(strerror(errno));
             }
             if(ftruncate(fd,size) == -1)
             {
                throw std::invalid_argument(strerror(errno));
             }
            auto  temp = reinterpret_cast<char *>(mmap(nullptr,size,PROT_READ | PROT_WRITE,
                                        MAP_SHARED | MAP_POPULATE | MAP_NONBLOCK,fd,0));
            if(memmove(temp,data_,size) == reinterpret_cast<void *>(-1))
            {
                throw std::invalid_argument(strerror(errno));
            }
            close(fd);
            msync(temp,size,0);//直接刷入磁盘之中
            munmap(temp,size);
        }
        catch (std::invalid_argument &e){
            puts(e.what());
        }
        return true;
    }
    //之后会添加Sync 同步写
private:
    int fd ; // open 的fd
    std::string filename; // 写入的文件名称
};
#endif //MY_REDIES_WRITE_FILE_H
