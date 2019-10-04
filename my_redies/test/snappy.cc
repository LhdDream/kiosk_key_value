//
// Created by kiosk on 19-9-2.
//
#include <snappy.h>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string input;
    for(size_t  i = 0; i < 10000 ; i++)
         input += "ppp";
    string output ;
    snappy::Compress(input.data(),input.size(),&output);
    cout << "size   " << input.size() << "out put " << output.size() << endl;
    string output_uncon;
    snappy::Compress(output.data(),output.size(),&output_uncon);
    cout << "size   " << output_uncon.size() << endl;
    string b;
    snappy::Uncompress(output_uncon.data(),output_uncon.size(),&b);
    string g;
    snappy::Uncompress(b.data(),b.size(),&g);
    std::cout << g << std::endl;
}
