//
// Created by kiosk on 2020/2/10.
//
#include <iostream>
#include "../src/core/db.h"
#include "../base/dict_builder.h"
#include <memory>
#include <chrono>
using namespace std;

char* randomstr()
{
    static char buf[1024];
    int len = rand() % 768 + 255;
    for (int i = 0; i < len; ++i) {
        buf[i] = 'A' + rand() % 26;
    }
    buf[len] = '\0';
    return buf;
}


int main(){


    std::unique_ptr<db> m_db= dict::Init("1.log","red");
    long long l = 0;
    std::string k[100000]{} ;
    for(int i = 0 ; i < 100000 ;i++){
        k[i] = randomstr();
        l += k[i].size();
    }
    std::string v = "123456789";
    l += 900000;

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    /*代码段*/
    for(int i = 0 ; i< 100000 ; i++){
         m_db->Set(k[i],v);
    }

    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
    std::cout << "time used ：" << time_used.count() << "seconds." << std::endl;
    std::cout << "data " << l/1024/1024  << " MB"<< std::endl;
    return 0;
}
