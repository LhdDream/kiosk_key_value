//
// Created by kiosk on 19-9-8.
//

#ifndef MY_REDIES_SDS_H
#define MY_REDIES_SDS_H
#include <string>
#include <cstring>
#include <cassert>
#include "../util/sparsepp/spp.h"
#include "../util/sparsepp/spp_utils.h"

//c++ string 是可以修改的 ,为了保证类型安全，在这里封装一下sds
class sds
{
public:
    sds() : data_(" "),size_(0){ }
    sds(const char * data,size_t n) : data_(data),size_(n){}
    //if no argument 空的字符串
    sds(const std::string &s) :size_(s.size()){
       data_ = new char [size_];
       strcpy(const_cast<char *> (data_),s.data());
    }

   sds(const char * data) : data_(data),size_(strlen(data)){
        data_ = new char [size_];
        strcpy(const_cast<char *> (data_),data);
    }
    sds(const sds &) = default;
    sds&operator=(const sds &) = default;
    [[nodiscard]] const char * data() const {return data_;}
    [[nodiscard]] size_t  size() const {return size_;}
    [[nodiscard]] bool empty() const {return size_ == 0;}
    char operator[](size_t n) const{
        assert(n >= 0);
        return data_[n];
    }
    [[nodiscard]] std::string Tostring() const { return std::string(data_,size_);}
    bool operator==( const sds& y) const {
        return ((this->size_ == y.size()) &&(memcmp(this->data(), y.data(), this->size()) == 0) );
    }
    bool  operator!=(const sds &y)const {
        return !(*this==y);
    }
private:
    const char *  data_;
    size_t  size_;
};


namespace  std{
    template <>
    struct hash<sds>{
        std::size_t operator()(const sds & p ) const{
            std::size_t seed = 0 ;
            spp::hash_combine(seed,p.Tostring());
            spp::hash_combine(seed,p.size());
            return seed;
        }
    };
}
#endif //MY_REDIES_SDS_H
