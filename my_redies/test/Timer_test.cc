//
// Created by kiosk on 19-10-6.
//
#include <iostream>
#include "../net/Timer.h"
#include <unistd.h>
using namespace std;
int main()
{
    std::shared_ptr<Timer> Timer_ = std::make_shared<Timer>([](){cout <<" s\n";},time(nullptr)+ 2 ,0);
    TimerQueue Timequeue_;
    Timequeue_.AddTimer(Timer_);
    sleep(8);
    Timequeue_.tick();
    return 0;
}
