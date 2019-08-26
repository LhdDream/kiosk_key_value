////
//// Created by kiosk on 19-8-17.
////
//#include "Acceptor.h"
//#include <fcntl.h>
//Acceptor::Acceptor() : idfd_(::open("/dev/null",O_RDONLY | O_CLOEXEC)),acceptSocket_(new Socket("127.0.0.1",8888)),listening_(false),acceptchannel_(new acChannel(acceptSocket_->fd()))
//{
//    acceptSocket_->bindaddress();
//
//}
//void Acceptor::listen() {
//    listening_ = true;
//    acceptSocket_->listen();
//    acceptchannel_->enableread();
//}
//void Acceptor::handleRead() {
//
//}