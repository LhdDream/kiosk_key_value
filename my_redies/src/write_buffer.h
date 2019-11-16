//
// Created by kiosk on 19-9-17.
//

#ifndef MY_REDIES_WRITE_BUFFER_H
#define MY_REDIES_WRITE_BUFFER_H
#include "../base/sds.h"
#include "../base/dict_builder.h"
#include <memory>
//计划将key和value 分离存储，尽量减少耦合度
//writebatch 写入磁盘
class write_buffer{
public:
    write_buffer() : dict_(std::make_unique<dict>()){
        std::cout << "write_buffer\n";
    };
    ~write_buffer() = default;
    void Set( const sds& key, const sds & value){
        dict_->Add(key,value);
    };
    bool Delete(const sds & key){
        return dict_->Delete(key);
    }
    bool Get(const sds & key,std::string * value){
        return dict_->Get(key,value);
    }
private:
    std::unique_ptr<dict> dict_;
};
#endif //MY_REDIES_WRITE_BUFFER_H
