//
// Created by kiosk on 19-10-29.
//

#ifndef MY_REDIES_FIFTER_BUILDER_H
#define MY_REDIES_FIFTER_BUILDER_H
#include "../util/bloom_filter.h"
//分为两种噢，过滤数据和索引数据
#include "../base/sds.h"
#include <vector>
class fifter{
public:
    explicit fifter() : bloom_(std::make_unique<bloom> ()) ,fifter_ (0),off_(0){

    }
    void Add(const sds & key_){
        std::string result_;
        bloom_->add(key_,&result_);
        fifter_.emplace_back(result_);
    }
   ~fifter() = default;
    std::string To_string() {
        off_ = 0;
        std::string result_;
        for(auto & it : fifter_)
        {
            it+= '\r';
            result_ += it;
        }
        off_ = result_.size();
        fifter_.clear();
        return result_;
    }
    //read 函数
    void SplitString(const std::string & s){
             if(!fifter_.empty())
             {
                 fifter_.clear();
             }
             std::string::size_type pos1 , pos2;
             pos2 = s.find('\r');
             pos1 = 0;
             while(std::string::npos != pos2)
             {
                 fifter_.emplace_back(s.substr(pos1,pos2-pos1));
                 pos1 = pos2 + 1;
                 pos2 = s.find('\r',pos1);
             }
             if(pos1 != s.length())
             {
                 fifter_.emplace_back(s.substr(pos1));
             }
    }
    bool match(sds & key_)
    {
        for(auto & it : fifter_)
        {
            if(bloom_->key_match(key_,&it))
            {
                return true;
            }
        }
        return false;
    }

    //分割函数
private:
    std::unique_ptr<bloom> bloom_;
    std::vector<std::string> fifter_;
    size_t  off_;
};
#endif //MY_REDIES_FIFTER_BUILDER_H
