//
// Created by kiosk on 19-8-16.
//
#include "Socket.h"
#include "../base/state.h"
#include <errno.h>
#include <netinet/tcp.h>
Socket::Socket(const char *ip, const uint16_t port)
{
    sockfd_ = socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,0);
    bzero(&address_ , sizeof(struct sockaddr_in));
    address_.sin_family = AF_INET;
    address_.sin_port = htons(port);
    inet_pton(AF_INET,ip,&address_.sin_addr);
}
Socket::~Socket() {
    ::close(sockfd_);
}
int Socket::listen() {
    return ::listen(sockfd_,20);
}
int Socket::bindaddress() {
    int res = 1;
    ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEADDR,&res,sizeof(int));
    ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEPORT,&res,sizeof(int));
    return ::bind(sockfd_,(struct sockaddr *)&address_,sizeof(struct sockaddr));
}
int Socket::accept() {
    struct sockaddr_in clientaddress_;
    socklen_t  client_addrlength_ = sizeof(clientaddress_);
    int fd = 0;
    fd = ::accept4(sockfd_, (struct sockaddr *) &clientaddress_, &client_addrlength_, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (fd < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return -1;
        }
    }
    return fd;
}
int Socket::defalutconnect() {
    struct sockaddr_in * addr;
    addr->sin_port = htons(8888);
    addr->sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&addr);
    socklen_t  addr_len = sizeof(addr);
    if(connect(sockfd_,(struct sockaddr *)&addr,sizeof(addr_len)) < 0 )
    {
        return ANET_ERR;
    }
    return ANET_OK;
}
int Socket::alive(int reuse)
{
    int resue = 1;
    if(::setsockopt(sockfd_,SOL_SOCKET,SO_KEEPALIVE,&resue,sizeof(int)) < 0)
    {
        return ANET_ERR;
    }
    resue = reuse;
    if(::setsockopt(sockfd_,IPPROTO_TCP,TCP_KEEPIDLE,&resue, sizeof(int)) < 0)
    {
        return ANET_ERR;
    }
    resue = reuse / 3;
    if(::setsockopt(sockfd_,IPPROTO_TCP,TCP_KEEPINTVL,&resue,sizeof(resue)) < 0)
    {
        return ANET_ERR;
    }
    if(::setsockopt(sockfd_,IPPROTO_TCP,TCP_KEEPCNT,&resue,sizeof(int)) < 0)
    {
        return ANET_ERR;
    }
    return ANET_OK;
}
int Socket::setTcpNolay(int reuse) // 开启的话输入１，不然 ０
{
    if(::setsockopt(sockfd_,IPPROTO_TCP,TCP_NODELAY,&reuse,sizeof(int)) < 0 )
    {
        return ANET_ERR;
    }
    return ANET_OK;
}
void Socket::shutdownWrite()
{
    if( ::shutdown(sockfd_,SHUT_WR)< 0 )
    {
        return ;
    }
}