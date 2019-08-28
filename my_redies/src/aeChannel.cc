//
// Created by kiosk on 19-8-28.
//
#include "aeChannel.h"

const int ReadEvent = EPOLLIN ;
const int WriteEvent = EPOLLOUT;
void aechannel::handleEvent() {
    if( events_  & ReadEvent ) {
        if(readcallback_) // 必须判断
        {
            readcallback_();
        }
    }
    if( events_ & WriteEvent)
    {
        if(writecallback_)
        {
            writecallback_();
        }
    }
}
void aechannel::handleRead( const Callback& cb)
{
    readcallback_ =  cb;
}
void aechannel::handleWrite(const Callback &cb)
{
    writecallback_ = cb;
}
void aechannel::enable_write()
{
    events_ |= WriteEvent;
}
void aechannel::enable_ET() {
    events_ |= EPOLLET;
    events_ |= ReadEvent;
}


