//
// Created by kiosk on 19-8-28.
//

#ifndef MY_REDIES_TIMEEVENTS__H
#define MY_REDIES_TIMEEVENTS__H
#include <functional>
// 时间事件处理函数
// 时间事件释放函数
class aeTimeEvent
{
public:
    aeTimeEvent();
    ~aeTimeEvent();
    typedef std::function< int() > aeTimeProc;
    typedef  std::function<void() > aeEvent;
    void settimeProc(aeTimeProc & db);
    void setEvent(aeEvent &db);
private:
    long long  id; //每一个时间事件的标识符
    long when_sec;//seconds
    long when_ms ;//milliseconds
    aeTimeProc timeProc;
    aeEvent eventproc;
};
#endif //MY_REDIES_TIMEEVENTS__H
