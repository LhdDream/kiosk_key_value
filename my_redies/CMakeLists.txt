cmake_minimum_required(VERSION 3.14)
project(my_redies)

set(CMAKE_CXX_STANDARD 11)

add_executable(my_redies main.cpp net/server.h net/anet.h net/ae_epoll.h src/aeEventloop.h net/ae_epoll.cc src/acChannelfd.h src/acChanneltime.h base/state.h net/Socket.h net/Socket.cc net/Acceptor.h net/Acceptor.cc base/dict.h base/dict.cc)