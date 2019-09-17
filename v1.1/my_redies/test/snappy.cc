//
// Created by kiosk on 19-9-2.
//
#include <snappy.h>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string input = "helloworld";
    string output ;
    for(size_t i = 0 ; i < 10 ; i++)
    {
        input += input;
    }
    snappy::Compress(input.data(),input.size(),&output);
    cout << "size   " << input.size() << "out put " << output.size() << endl;
    string output_uncon;
    snappy::Uncompress(output.data(),output.size(),&output_uncon);
    if(output_uncon == input)
    {
        std::cout << output_uncon << std::endl;
    }
}
