//
// Created by kiosk on 19-9-17.
//

#ifndef MY_REDIES_WRITE_BUFFER_H
#define MY_REDIES_WRITE_BUFFER_H
#include "sds.h"
//计划将key和value 分离存储，尽量减少耦合度
class write_buffer{
public:
    class Handler {
    public:
        virtual ~Handler();
        virtual void Set(const sds &key,const sds & value) = 0 ;
        virtual void Delete(const sds & key) = 0;
    };
    write_buffer();
    write_buffer(const write_buffer&) = default;
    write_buffer& operator=(const write_buffer&) = default;
    ~write_buffer() = default;
    void Set(const sds& key,const sds & value);
    void Delete(const sds & key);
    void clear();
private:
    std::string key_buffer; //key 缓冲
    std::string value_buffer;//value 缓冲
};
#endif //MY_REDIES_WRITE_BUFFER_H
