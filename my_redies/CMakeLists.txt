cmake_minimum_required(VERSION 3.14)
project(my_redies)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_redies main.cpp base/state.h test/snappy.cc base/skiplist.h base/skiplist.cc util/Prena.h util/Prena.cc test/anytest.cc test/test.cc base/random.h test/random.cc test/skiplisttest.cc base/sds.h test/coding.cc base/options.h util/bloom_filter.h util/hash.h test/bloom_test.cc base/dict_builder.h base/dict_builder.cc src/write_buffer.h src/db.h src/db_wr.h src/db_wr.cc test/do.cc test/cache.cc table/sstable.h net/Timer.h test/Timer_test.cc src/Compaction.h src/Compaction.cc table/sstable.cc base/decondig.h base/decondig.cc table/write_file.h)