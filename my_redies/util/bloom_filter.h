//
// Created by kiosk on 19-9-14.
//

#ifndef MY_REDIES_BLOOM_FILTER_H
#define MY_REDIES_BLOOM_FILTER_H
#include <bitset>
#include "hash.h"
#include <functional>
#include <vector>
#include <any>
#include "../base/sds.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
//this file create bloom
//bloom 过滤器表示如果不在这个集合之中，则说明不在，在这个集合之后，实时不一定在这个集合之中
class bloom
{
public:
    bloom(){
        array.reset();
    }
    void add(const sds &Temp);
    void write_(std::string & filename, unsigned long long *file_size ){
        *file_size += 2048;
        int fd = open(filename.c_str(),O_APPEND | O_WRONLY | O_CREAT ,S_IRUSR | S_IWUSR );
        struct stat sb{};
        if((fstat(fd,&sb)) == -1)
        {
            return ;
        }
        if((ftruncate(fd,*file_size ) )== -1) //使用mmap之前必须扩大文件大小，因为mmap写入不能大于文件大小
        {
            return ;
        }
        char *memPtr;
        memPtr = (char *)mmap(nullptr, *file_size  , PROT_READ | PROT_WRITE,
                              MAP_SHARED, fd, 0);
        memmove(memPtr,(char *)&array, *file_size ); // 写入1KB的fifter
        msync(memPtr,*file_size ,0);
        munmap(memPtr,*file_size );
        close(fd);
    }

private:
    std::bitset<16 * 1024> array; //2KB
};

 void  bloom::add(const sds &Temp) {
        array.set(SDBMHash(Temp.data()));
        array.set(RSHash(Temp.data()));
        array.set(JSHash(Temp.data()));
        array.set(APHash(Temp.data()));
        array.set(PJWHash(Temp.data()));
}


#endif //MY_REDIES_BLOOM_FILTER_H
