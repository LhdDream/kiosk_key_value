//
// Created by kiosk on 19-8-28.
//

#ifndef MY_REDIES_TCPCONNECTION_H
#define MY_REDIES_TCPCONNECTION_H
#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../net/Socket.h"
#include "aeEventloop.h"
#include "aeChannel.h"
class Socket;
class aechannel;
class aeEventloop;
//返回一个指向自身的enable_shared_from_this 指针
//tcpconnection 　管理所有的acceptor  socket
//
class Tcpconnection;
typedef  std::shared_ptr<Tcpconnection> Tcpptr;
class Tcpconnection : public boost::enable_shared_from_this<Tcpconnection>
{
public:
    // 连接来临的回调函数
    //初始化各种回调函数
    Tcpconnection(aeEventloop * loop,int sockfd): loop_(loop),sockfd_(new Socket(sockfd)),channel_(new aechannel(loop_.get(),sockfd))
    {
        channel_->handleRead(std::bind(&Tcpconnection::handleread,this));
        channel_->handleWrite(std::bind(&Tcpconnection::handlewrite,this));
    }
    ~Tcpconnection() {};
    void connect();
    void handleread();
    void handlewrite();
private:
    // 如果套接子可读触发相应的事件
    //  这里需要一个改变tcp 连接状态的函数
    // 接受到http请求之后立马注册epollout 时间，如果可写就写入
    std::unique_ptr<aeEventloop> loop_ ;
    std::unique_ptr<Socket> sockfd_;
    std::unique_ptr<aechannel> channel_;
};
//指向自身的shared_ptr 指针,tcpconnectionptr

#endif //MY_REDIES_TCPCONNECTION_H
