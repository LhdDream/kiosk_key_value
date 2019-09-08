//
// Created by kiosk on 19-9-3.
//
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <boost/any.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace boost;
int main()
{
    std::vector<boost::spirit::hold_any> b;
    b.push_back(boost::spirit::hold_any('d'));
    b.push_back(boost::spirit::hold_any(3));
    b.push_back(boost::spirit::hold_any('f'));
    for(auto &c : b)
    {
        if(c.type() == typeid(int))
        {
            std::cout << c <<std::endl;
        }
    }
   // std::cout << b[0] << std::endl;
    //std::cout << b[1] << std::endl;

    return 0;
}
