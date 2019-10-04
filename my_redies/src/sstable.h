//
// Created by kiosk on 19-10-1.
//

#ifndef MY_REDIES_SSTABLE_H
#define MY_REDIES_SSTABLE_H

#include <vector>
#include <string>
#include "../base/options.h"
#include <algorithm>
#include "../base/sds.h"
#include "../util/bloom_filter.h"
#include "../util/parallel_hashmap/phmap.h"
#include <snappy.h>
using phmap::parallel_flat_hash_map;
class sstable{
public:
    explicit sstable() : ht_(std::make_unique<parallel_flat_hash_map<sds,sds,HashFunc,EqualKey>>()){

    };
    ~sstable() = default;
    void save(std::unique_ptr<bloom> & bloom_){
         std::string name(std::to_string(id) + ".tss");
         bloom_->write_(name);
         std::string buf;//作为一个标志
         append_(buf);
         std::string write__;
         snappy::Compress(buf.data(),buf.size(),&write__);
         size = write__.size();
         write__ += std::to_string(size) + write__;
         write_(name,write__);
         id++;
    }
    void swap(std::unique_ptr< parallel_flat_hash_map<sds,sds,HashFunc,EqualKey> > &ht){
        ht_.swap(ht);
    }
    void append_(std::string & buf){
        for(auto &c : *ht_){
            buf.append(c.first.Tostring());
            buf.append(c.second.Tostring());
        }
    }
    void write_(std::string &filename,std::string &buf){
        int fd = open(filename.c_str(),O_APPEND | O_WRONLY | O_CREAT ,S_IRUSR | S_IWUSR );
        struct stat sb{};
        if((fstat(fd,&sb)) == -1)
        {
            return ;
        }
        if((ftruncate(fd,1024 + size) )== -1) //使用mmap之前必须扩大文件大小，因为mmap写入不能大于文件大小
        {
            return ;
        }
        char *memPtr;
        memPtr = (char *)mmap(nullptr, 1024 + size , PROT_READ | PROT_WRITE,
                              MAP_SHARED, fd, 0);
        memmove(memPtr,buf.c_str(), buf.size()); // 写入1KB的fifter
        msync(memPtr,buf.size(),0);
        munmap(memPtr,buf.size());
        close(fd);
    }
private:
    std::unique_ptr< parallel_flat_hash_map<sds,sds,HashFunc,EqualKey> >  ht_;
    unsigned  long long id  = 0; // 标记打开是第几块的sstable
    unsigned  long long size = 0;
};
#endif //MY_REDIES_SSTABLE_H
