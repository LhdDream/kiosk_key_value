//
// Created by kiosk on 19-8-28.
//

#ifndef MY_REDIES_AECHANNEL_H
#define MY_REDIES_AECHANNEL_H
#include <functional>
#include "aeEventloop.h"
#include <sys/epoll.h>
class aeEventloop;
class aechannel
{
public:
    typedef std::function< void() > Callback;
    aechannel(aeEventloop *loop_, int fd) : fd_(fd),events_(0),flag(0){
    };
    ~aechannel() {};
    void handleEvent();
    int fd() const {return fd_;}
    void enable_write();
    void enable_ET();
    void  set_events(int events) {   events_ = events;}
    void  set_flag(int flag_) { flag = flag_ ;}
    int get_flag() {return flag;}
    bool hasnoevent(){ return events_ == 0; }
    int get_events(){return events_;};
    void handleRead(const  Callback &cb);
    void handleWrite(const Callback &cb);
private:
    int fd_;
    int events_;
    int flag ;
    Callback readcallback_;
    Callback writecallback_;
};
#endif //MY_REDIES_AECHANNEL_H
