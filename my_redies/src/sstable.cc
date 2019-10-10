//
// Created by kiosk on 19-10-7.
//
#include "sstable.h"
void sstable::write_file(std::string &name,std::string &buffer) {
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
    memPtr = (char *)mmap(nullptr, 10 , PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, 0);
    printf("%s %lu\n",buffer.c_str(),buffer.size());
    if (memmove(memPtr, buffer.c_str(), 10) == (void *)-1)
    {
        perror(strerror(errno));
    }
    printf("%s %lu\n",buffer.c_str(),buffer.size());
    msync(memPtr,buffer.size(),0);
    munmap(memPtr,buffer.size());
    close(fd);
}
void sstable::append(std::string &buffer) {
    std::sort(recode_.begin(),recode_.end());
    //重启点加入
    buffer.append(std::to_string(restarte_.size()));
    for(auto &p : restarte_)
    {
        buffer.append(std::to_string(strlen(p.key_length)));
        buffer.append(p.key_length);
        buffer.append(p.key_.Tostring());
        buffer.append(std::to_string(strlen(p.offest_)));
        buffer.append(p.offest_);
    }
    //读取所有重启点进行二分查找
    for(auto &c : recode_)
    {
        buffer.append(std::to_string(c.key_len().size()));
        buffer.append(c.key_len());
        buffer.append(c.key_());
        buffer.append(std::to_string(c.value_len().size()));
        buffer.append(c.value_len());
        buffer.append(c.value_());
    }
}