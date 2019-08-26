//
// Created by kiosk on 19-8-16.
//
#include "Socket.h"
#include <errno.h>
#include <netinet/tcp.h>
Socket::Socket(const char *ip, const uint16_t port)
{
    sockfd_ = socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK,0);
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
    ::setsockopt(AF_INET,SOL_SOCKET,SO_REUSEADDR,&res,sizeof(int));
    ::setsockopt(AF_INET,SOL_SOCKET,SO_REUSEPORT,&res,sizeof(int));
    ::setsockopt(AF_INET,SOL_SOCKET,SO_KEEPALIVE,&res,sizeof(int));
    return ::bind(sockfd_,(struct sockaddr *)&address_,sizeof(struct sockaddr));
}
int Socket::accept() {
    struct sockaddr_in clientaddress_;
    socklen_t  client_addrlength_ = sizeof(clientaddress_);
    int fd = 0;
    while(1) {
        fd = ::accept4(sockfd_, (struct sockaddr *) &clientaddress_, &client_addrlength_, SOCK_NONBLOCK);
        if (fd < 0) {
            if (errno == EWOULDBLOCK) {
                continue;
            } else {
                return -1;
            }
        }
        if(fd > 0)
        {
            int val =1;
            ::setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val));
            //这里使用tcpNagle 尽可能发大包
        }
        break;
    }
    return fd;
}
void Socket::shutdownWrite()
{
    if( ::shutdown(sockfd_,SHUT_WR)< 0 )
    {
        return ;
    }
}