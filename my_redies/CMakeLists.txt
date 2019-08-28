cmake_minimum_required(VERSION 3.14)
project(my_redies)

set(CMAKE_CXX_STANDARD 11)

add_executable(my_redies main.cpp src/aeEventloop.h base/state.h net/Socket.h net/Socket.cc base/dict.h base/dict.cc src/aeEventloop.cc src/timeevents_.h src/timeevents_.cc src/aeChannel.h src/aeChannel.cc src/Tcpconnection.h src/Tcpconnection.cc)