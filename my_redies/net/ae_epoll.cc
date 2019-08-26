////
//// Created by kiosk on 19-8-15.
////
//#include "ae_epoll.h"
//#include "../src/acChannelfd.h"
//#include <unistd.h>
//#include <sys/epoll.h>
//#include <string.h>
//#include <fcntl.h>
//ae_epoll::ae_epoll(aeEventloop *eventloop) : owenerloop(eventloop),epfd(epoll_create1(EPOLL_CLOEXEC)),events_(1024),event_(& events_)
//{
//}
//ae_epoll::~ae_epoll()
//{
//    ::close(epfd);
//}
//
//int ae_epoll::aeepoll(struct timeval *tvp , channlist_ * activeChannels) {
//    int retval,numevents = 0;
//    retval = epoll_wait(epfd,&*events_.begin(),owenerloop->getsize(),tvp ?(tvp->tv_sec * 1000 + tvp->tv_usec/1000) : -1);
//    if(retval > 0 ) //遍历循环
//    {
//       fillActiveChannels(retval,activeChannels);
//       //遍历循环，将活跃的fd存入到channel之中
//       if( numevents == events_.size())
//       {
//           events_.resize( 2 * events_.size());
//       }
//    }
//}
//void ae_epoll::fillActiveChannels(int num , channlist_ * activechnnels) const
//{
//    if(num < events_.size())
//    {
//        return ;
//    }
//    for(int i = 0 ; i < num ; ++i)
//    {
//        //获取活跃的连接存入列表之中
//        acChannel* channel_ = channels_[events_[i].data.fd];
//        channel_->set_events(events_[i].events);
//        channel_->set_fd(events_[i].data.fd);
//        activechnnels->push_back(channel_);
//        channels_[events_[i].data.fd] = channel_;
//    }
//}
//void ae_epoll::updatachannel(acChannel * channel_)
//{
//    int fd = channel_->fd();
//    if(channels_.find(fd) == channels_.end())
//    {
//        update(EPOLL_CTL_ADD,channel_);
//        channels_[channel_->fd()] = channel_;
//    }
//    else if(channels_.find(fd) != channels_.end())
//    {
//        if(channel_->state_()) {
//            update(EPOLL_CTL_DEL,channel_);
//            channels_.erase(channel_->fd());
//        }
//        channels_[channel_->fd()] = channel_;
//    }
//}
//void ae_epoll::update(int operation,acChannel * channel)
//{
//    struct epoll_event events_;
//    bzero(&events_,sizeof(events_));
//    events_.events = channel->stats_();
//    events_.data.fd = channel->fd();
//    if(::epoll_ctl(epfd,operation,events_.data.fd,&events_) < 0)
//    {
//        perror("epoll_ctl error");
//    }
//}