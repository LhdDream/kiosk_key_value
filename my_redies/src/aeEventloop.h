//
// Created by kiosk on 19-8-15.
//

#ifndef MY_REDIES_AEEVENTLOOP_H
#define MY_REDIES_AEEVENTLOOP_H
#include <memory>
#include <vector>
#include <atomic>
#include <functional>
#include <list>
#include "../base/state.h"
#include "timeevents_.h"

class aeEventloop
{
public:
    typedef  std::function< void()> aebefore;
    aeEventloop();
    ~aeEventloop();
    void loop() ; //开启事件循环
    int aeProcessEvents(int flags);
private:
    int maxfd;
    int setsize;
    long long timeNextid;
    time_t  lastTime;
    std::atomic<bool> stop;
    aebefore before;
    std::list <aeTimeEvent> timeEventHead;
};
#endif //MY_REDIES_AEEVENTLOOP_H
