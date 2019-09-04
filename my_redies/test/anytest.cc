//
// Created by kiosk on 19-9-3.
//
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace boost;
int main()
{
    std::vector<boost::spirit::hold_any> b;
    b.push_back(boost::spirit::hold_any('d'));
    b.push_back(boost::spirit::hold_any(3));
    std::cout << b[0] << std::endl;
    std::cout << b[1] << std::endl;

    return 0;
}
