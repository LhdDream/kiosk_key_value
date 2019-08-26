////
//// Created by kiosk on 19-8-15.
////
//
//#ifndef MY_REDIES_AE_EPOLL_H
//#define MY_REDIES_AE_EPOLL_H
//
//#include "../src/aeEventloop.h"
//#include "../src/acChannelfd.h"
//#include <boost/enable_shared_from_this.hpp>
//#include <memory>
//#include <vector>
//#include <time.h>
//#include <map>
////eventloop　中的epoll
//
//class ae_epoll : boost::enable_shared_from_this<ae_epoll>
//{
// public:
//    typedef std::vector< acChannel * > channlist_;
//    ae_epoll(aeEventloop * eventloop);
//    //关联事件fd
//    //返回epoll时间个数
//    int aeepoll(struct timeval *tvp,channlist_ * activeChannels);
//    void updatachannel(acChannel * channel_);
//    ~ae_epoll(); // 析够函数不应该带参数
//    void update(int operation,acChannel* channel);
// private:
//    void fillActiveChannels(int num , channlist_ * activechnnels) const;
//    int epfd;
//    std::unique_ptr<std::vector<struct epoll_event> >event_;
//    std::vector<struct epoll_event> events_;
//    aeEventloop * owenerloop;
//    typedef std::map<int ,acChannel *> channelMap;
//    channelMap channels_; // 记录被连接之后的fd和相应的IO分发器
//    //命令相应和恢复时间　 time时间事件循环
//};
//#endif //MY_REDIES_AE_EPOLL_H
