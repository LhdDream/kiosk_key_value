cmake_minimum_required(VERSION 3.14)
project(my_redies)

set(CMAKE_CXX_STANDARD 17)

link_libraries(-lsnappy)
add_executable(my_redies main.cpp base/dict_builder.cc    src/db_wr.cc     src/Compaction.cc  base/decondig.cc table/block_builder.cc  table/Block.cc   src/read_buffer.cc)