//
// Created by kiosk on 19-11-3.
//
#include <iostream>
using namespace std;
int main()
{
    std::string fiilename = "aaa\r1ffas\r";
    std::string n;
    n.resize(100);
    std::string p;
    auto it = fiilename.find('\r');
    std::copy(fiilename.begin() , fiilename.begin()+it,n.begin());
    std::cout << n <<std::endl;
}
