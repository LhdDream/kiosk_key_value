//
// Created by kiosk on 19-9-8.
//

#ifndef MY_REDIES_SDS_H
#define MY_REDIES_SDS_H
#include <string>
#include <cstring>
#include <cassert>


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
    [[nodiscard]] const char * data() const {return data_;}
    [[nodiscard]] size_t  size() const {return size_;}

    [[nodiscard]] bool empty() const {return size_ == 0;}

    char operator[](size_t n) const{
        assert(n >= 0);
        return data_[n];
    }
    void removesize(size_t n ){
        assert(n >= 0);
        data_ += n;
        size_ -= n;
    }
    [[nodiscard]] std::string Tostring() const { return std::string(data_,size_);}
    inline bool operator == (const sds &s) const{
        return ((s.size_ == this->size_) && (memcmp(this->data(),s.data_,this->size_) == 0));
        //memcmp比较内存的前n个字节想不想等如果相等返回0
    }
    inline bool  operator != (const sds &s) const{
        return !(*this == s);
    }
private:
    const char *  data_;
    size_t  size_;
};
struct HashFunc{
    std::size_t operator()(const sds & p ) const{
        using std::size_t ;
        using std::hash;
        return hash<std::string>()(p.Tostring());
    }
};
struct EqualKey
{
    bool operator () (const sds & p, const sds & s) const{
        return p == s;
    }
};
#endif //MY_REDIES_SDS_H
