//
// Created by kiosk on 19-9-15.
//
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
int main()
{
    std::vector<std::string> a;
    a.emplace_back("pppp");
    a.emplace_back("aaaa");
    a.emplace_back("dddd");
    std::sort(a.begin(),a.end());
    for(auto &c : a)
    {
        std::cout << c << std::endl;
    }
    return 0;
}
