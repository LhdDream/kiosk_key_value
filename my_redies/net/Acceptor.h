//
// Created by kiosk on 19-8-16.
//

#ifndef MY_REDIES_ACCEPTOR_H
#define MY_REDIES_ACCEPTOR_H
#include "Socket.h"
#include "../src/acChannelfd.h"
#include "../src/aeEventloop.h"
#include <memory>
class Acceptor
{
public:
    // 新连接发来的时候来一个回调
    typedef std::function<void (int sockfd) > ConnCallback;
    explicit  Acceptor();
    ~Acceptor();
    void setCallback(const ConnCallback & new_){
        NewCallback_ = new_;
    }
    void listen();
    //初始化listen ,把listen添加到fd之中，通过channel 来进行事件分发
    bool listening(){ return listening_;}
    void handleRead() ;
    void handleWrite() ;
private:
    std::unique_ptr<Socket> acceptSocket_;  // 对于socket 的指向
    std::unique_ptr<acChannel> acceptchannel_; //
    bool listening_ ; //有没有监听
    int idfd_; //防止文件描述符被耗尽
    ConnCallback NewCallback_;
};
#endif //MY_REDIES_ACCEPTOR_H
