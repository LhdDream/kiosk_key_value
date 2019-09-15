cmake_minimum_required(VERSION 3.14)
project(my_redies)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_redies main.cpp src/aeEventloop.h base/state.h net/Socket.h net/Socket.cc src/aeEventloop.cc src/timeevents_.h src/timeevents_.cc src/aeChannel.h src/aeChannel.cc src/Tcpconnection.h src/Tcpconnection.cc test/snappy.cc base/deconding.h base/deconding.cc base/skiplist.h base/skiplist.cc util/Prena.h util/Prena.cc test/anytest.cc test/test.cc base/random.h test/random.cc test/skiplisttest.cc base/sds.h test/coding.cc src/Cache.h src/Cache.cc src/command.h src/command.cc base/options.h util/bloom_filter.h util/hash.h test/bloom_test.cc src/dbupdate.h src/dbupdate.cc test/phmap.cc base/dict_builder.h base/dict_builder.cc)