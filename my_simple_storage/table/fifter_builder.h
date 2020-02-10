//
// Created by kiosk on 19-10-29.
//

#ifndef MY_SIMPLE_STORAGE_BUILDER_H
#define MY_SIMPLE_STORAGE_BUILDER_H
#include "../util/bloom_filter.h"
//分为两种噢，过滤数据和索引数据
#include <vector>
class fifter{
public:
    explicit fifter() : m_bloom(std::make_unique<bloom> ()) ,m_fifter (0){
    }
    ~fifter() = default;
    void Add(const std::string & key_){
        std::string result_;
        m_bloom->Add(key_,result_);
        m_fifter.emplace_back(result_);
    }
    std::string To_string() {
        std::string result_;
        for(auto & it : m_fifter)
        {
            it+= '\r';
            result_ += it;
        }
        m_fifter.clear();
        return result_;
    }
    //read 函数
    void SplitString(const std::string & s){
             if(!m_fifter.empty())
             {
                 m_fifter.clear();
             }
             std::string::size_type pos1 , pos2;
             pos2 = s.find('\r');
             pos1 = 0;
             while(std::string::npos != pos2)
             {
                 m_fifter.emplace_back(s.substr(pos1,pos2-pos1));
                 pos1 = pos2 + 1;
                 pos2 = s.find('\r',pos1);
             }
             if(pos1 != s.length())
             {
                 m_fifter.emplace_back(s.substr(pos1));
             }
    }
    bool Match(std::string & key_)
    {
        for(auto & it : m_fifter)
        {
            if(m_bloom->Key_Match(key_,it))
            {
                return true;
            }
        }
        return false;
    }
private:
    std::unique_ptr<bloom> m_bloom;
    std::vector<std::string> m_fifter;
};
#endif //MY_REDIES_m_fifterBUILDER_H
