//
// Created by kiosk on 19-8-16.
//

#ifndef MY_REDIES_SOCKET_H
#define MY_REDIES_SOCKET_H
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
class Socket
{
public:
    //shutdown 会让对端把应该发的数据收到
    Socket(const char * ip ,const uint16_t port);
    int fd() { return sockfd_; }
    int listen();
    int bindaddress();
    int accept();
    void shutdownWrite();
    ~Socket();
private:
    int sockfd_;
    struct sockaddr_in address_;
};
#endif //MY_REDIES_SOCKET_H
