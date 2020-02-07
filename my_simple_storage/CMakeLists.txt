cmake_minimum_required(VERSION 3.14)
project(my_redies)

set(CMAKE_CXX_STANDARD 17)

include_directories(base net src table  util)

aux_source_directory(base SOURCE_BASE)
aux_source_directory(net SOURCE_NET)
aux_source_directory(src SOURCE_SRC)
aux_source_directory(table SOURCE_TABLE)
aux_source_directory(util SOURCE_UTIL)

link_libraries(-lsnappy)
add_definitions("--std=c++14")
add_definitions("-g")

add_executable(my_redies main.cpp
        ${SOURCE_BASE}
        ${SOURCE_NET}
        ${SOURCE_SRC}
        ${SOURCE_TABLE}
        ${SOURCE_UTIL}
        )