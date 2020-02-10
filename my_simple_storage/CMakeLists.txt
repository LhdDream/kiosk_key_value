cmake_minimum_required(VERSION 3.14)
project(my_simple_storage)

set(CMAKE_CXX_STANDARD 14)

include_directories(base net src  log table  util config )

aux_source_directory(base SOURCE_BASE)
aux_source_directory(net SOURCE_NET)
aux_source_directory(log SOURCE_LOG)
aux_source_directory(table SOURCE_TABLE)
aux_source_directory(util SOURCE_UTIL)
aux_source_directory(config SOURCE_CONFIG)
aux_source_directory(src/compaction SOURCE_COMPACTION)
aux_source_directory(src/core SOURCE_CORE)
aux_source_directory(src/version SOURCE_VERSION)


link_libraries(-lsnappy)
add_definitions("--std=c++14")
add_definitions("-g")

add_executable(my_simple_storage main.cpp
        ${SOURCE_BASE}
        ${SOURCE_NET}
        ${SOURCE_LOG}
        ${SOURCE_TABLE}
        ${SOURCE_UTIL}
        ${SOURCE_CONFIG}
        ${SOURCE_COMPACTION}
        ${SOURCE_CORE}
        ${SOURCE_VERSION}
       )