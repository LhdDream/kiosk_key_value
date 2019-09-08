//
// Created by kiosk on 19-9-8.
//

#ifndef MY_REDIES_SDS_H
#define MY_REDIES_SDS_H
#include <string>
#include <cstring>
#include <assert.h>
//c++ string 是可以修改的 ,为了保证类型安全，在这里封装一下sds
class sds
{
public:
    sds() : data_(" "),size_(0){ }
    sds(const char * data,size_t n) : data_(data),size_(n){}
    //if no argument 空的字符串
    sds(const std::string &s) :data_(s.data()),size_(s.size()){}
    sds(const char * data) : data_(data),size_(strlen(data)){}

    sds(const sds &) = default;
    sds&operator=(const sds &) = default;

    const char * data() const {return data_;}
    size_t  size() const {return size_;}

    bool empty() const {return size_ == 0;}

    char operator[](size_t n) const{
        assert(n >= 0);
        return data_[n];
    }
    void removesize(size_t n ){
        assert(n >= 0);
        data_ += n;
        size_ -= n;
    }
    std::string Tostring() const { return std::string(data_,size_);}
    inline bool operator == (const sds &s) const{
        return ((s.size_ == this->size_) && (memcmp(this->data(),s.data_,this->size_)));
    }
    inline bool  operator != (const sds &s) const{
        return !(*this == s);
    }
private:
    const char *  data_;
    size_t  size_;
};

#endif //MY_REDIES_SDS_H
