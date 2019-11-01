cmake_minimum_required(VERSION 3.14)
project(my_redies)

set(CMAKE_CXX_STANDARD 17)

link_libraries(-lsnappy)
add_executable(my_redies main.cpp base/state.h  base/skiplist.h base/skiplist.cc util/Prena.h util/Prena.cc  base/random.h   base/sds.h  base/options.h util/bloom_filter.h util/hash.h  base/dict_builder.h base/dict_builder.cc src/write_buffer.h src/db.h src/db_wr.h src/db_wr.cc   table/sstable.h net/Timer.h  src/Compaction.h src/Compaction.cc base/decondig.h base/decondig.cc table/write_file.h util/sparsepp/FileSerializer.h util/memorypool/memorypool.h  util/memorypool/memorypool.cc table/log.h table/Block.h table/block_builder.h table/block_builder.cc test/smaz.cc test/test.cc table/Block.cc src/lru.h table/fifter_builder.h src/read_buffer.h)