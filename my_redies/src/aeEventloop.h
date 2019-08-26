//
// Created by kiosk on 19-8-15.
//

#ifndef MY_REDIES_AEEVENTLOOP_H
#define MY_REDIES_AEEVENTLOOP_H
#include <time.h>
#include <memory>
#include <vector>
#include "../net/ae_epoll.h"
#include "acChannelfd.h"
#include "acChanneltime.h"
class ae_epoll;
class acChannelfd;
class acChanneltime;
class aeEventloop
{
public:
    aeEventloop();
    ~aeEventloop();
    int getsize() { return setsize_;}
private:
    int setsize_; // 限制文件描述符的多少
    time_t lasttime_;//最后一次执行事件的时间
    long long timeID_; // 时间事件的id, 在这里构建一个链表，里面进行存储
    std::shared_ptr<ae_epoll> point_ep;
    std::vector<acChannelfd> channelsfd_;
    std::vector<acChanneltime> channeltime_;
};
#endif //MY_REDIES_AEEVENTLOOP_H
