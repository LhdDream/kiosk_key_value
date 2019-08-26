////
//// Created by kiosk on 19-8-15.
////
//
//#ifndef MY_REDIES_ACCHANNEL_H
//#define MY_REDIES_ACCHANNEL_H
//#include <functional>
//#include "../base/state.h"
//#include "../net/ae_epoll.h"
////注册可读可写时间，文件事件
//class ae_epoll;
//class acChannel // 事件分发器
//{
//public:
//    typedef std::function<void()> event;
//    acChannel(int sockfd);
//    void set_events(int events){
//        mask_ = events;
//    }
//    void set_fd(int fd){fd_ = fd;}
//    int fd() { return fd_;}
//    bool state_() {return mask_ == AE_NONE ; }
//    int stats_() {return mask_;}
//    void set_handelread(event & read)
//    {
//        read_ = read;
//    }
//    void set_handelwrite(event & write)
//    {
//        write_ = write;
//    }
//    void enableread()
//    {
//        mask_ |= AE_READABLE;
//    }
//    void enablewrite()
//    {
//        mask_ |= AE_WRITABLE;
//    }
//private:
//    int mask_; //  标志可读可写事件
//    //注册一个读处理器
//    //一个写处理器
//    int fd_;
//    event read_; // 读事件
//    event write_; //写事件
//    std::unique_ptr<ae_epoll> epoll_; //里面有epoll指向自身
//};
//#endif //MY_REDIES_ACCHANNEL_H
