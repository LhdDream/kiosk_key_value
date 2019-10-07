//
// Created by kiosk on 19-10-7.
//
#include "sstable.h"
void sstable::write_file(std::string &name) {
    file_size += recode_.size();
    int fd = open(name.c_str(),O_APPEND | O_WRONLY | O_CREAT ,S_IRUSR | S_IWUSR );
    struct stat sb{};
    if((fstat(fd,&sb)) == -1)
    {
        return ;
    }
    if((ftruncate(fd,file_size) )== -1) //使用mmap之前必须扩大文件大小，因为mmap写入不能大于文件大小
    {
        return ;
    }
    char *memPtr;
    memPtr = (char *)mmap(NULL, file_size , PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, 0);
    memmove(memPtr,(char *)&array, 1024); // 写入1KB的fifter
    msync(memPtr,1024,0);
    munmap(memPtr,1024);
    close(fd);
}
void sstable::append(std::string &buffer) {
    for(auto &c : recode_)
    {

    }
}