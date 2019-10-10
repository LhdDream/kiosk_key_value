#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include "../base/decondig.h"
#include "../base/decondig.cc"
#include <memory>
using namespace std;

class K{
public:
    K(){
        a[0] = 1;
    }
    void clear()
    {
        a[0] = 0 ;
    }
    void print()
    {
        std::cout << a[0] << std::endl;
    }
    ~K() = default;
    int a[3];
};
int main()
{
    int b = 2;
    K b1;
    std::shared_ptr<K > c(std::make_shared<K>(b1));
    std::vector<std::shared_ptr<K >> d;
    d.emplace_back(std::move(c));
    c = std::make_shared<K>(b1);
    c->clear();
    for(auto &p : d)
    {
        p->print();
    }
}

