//
// Created by kiosk on 19-9-26.
//
#include <iostream>
#include <list>
#include <ctime>
#include <unistd.h>
using namespace std;
int main()
{
    time_t stamp;
   for(auto c = 0 ;c < 100000 ;c++)
   {
       std::cout << time(&stamp) << std::endl;
       sleep(2);
   }
}
