# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kiosk/CLionProjects/my_redies

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kiosk/CLionProjects/my_redies/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/my_redies.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_redies.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_redies.dir/flags.make

CMakeFiles/my_redies.dir/main.cpp.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_redies.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/main.cpp.o -c /home/kiosk/CLionProjects/my_redies/main.cpp

CMakeFiles/my_redies.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/main.cpp > CMakeFiles/my_redies.dir/main.cpp.i

CMakeFiles/my_redies.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/main.cpp -o CMakeFiles/my_redies.dir/main.cpp.s

CMakeFiles/my_redies.dir/test/snappy.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/snappy.cc.o: ../test/snappy.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_redies.dir/test/snappy.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/snappy.cc.o -c /home/kiosk/CLionProjects/my_redies/test/snappy.cc

CMakeFiles/my_redies.dir/test/snappy.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/snappy.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/snappy.cc > CMakeFiles/my_redies.dir/test/snappy.cc.i

CMakeFiles/my_redies.dir/test/snappy.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/snappy.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/snappy.cc -o CMakeFiles/my_redies.dir/test/snappy.cc.s

CMakeFiles/my_redies.dir/base/skiplist.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/base/skiplist.cc.o: ../base/skiplist.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_redies.dir/base/skiplist.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/base/skiplist.cc.o -c /home/kiosk/CLionProjects/my_redies/base/skiplist.cc

CMakeFiles/my_redies.dir/base/skiplist.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/base/skiplist.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/base/skiplist.cc > CMakeFiles/my_redies.dir/base/skiplist.cc.i

CMakeFiles/my_redies.dir/base/skiplist.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/base/skiplist.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/base/skiplist.cc -o CMakeFiles/my_redies.dir/base/skiplist.cc.s

CMakeFiles/my_redies.dir/util/Prena.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/util/Prena.cc.o: ../util/Prena.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_redies.dir/util/Prena.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/util/Prena.cc.o -c /home/kiosk/CLionProjects/my_redies/util/Prena.cc

CMakeFiles/my_redies.dir/util/Prena.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/util/Prena.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/util/Prena.cc > CMakeFiles/my_redies.dir/util/Prena.cc.i

CMakeFiles/my_redies.dir/util/Prena.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/util/Prena.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/util/Prena.cc -o CMakeFiles/my_redies.dir/util/Prena.cc.s

CMakeFiles/my_redies.dir/test/anytest.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/anytest.cc.o: ../test/anytest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_redies.dir/test/anytest.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/anytest.cc.o -c /home/kiosk/CLionProjects/my_redies/test/anytest.cc

CMakeFiles/my_redies.dir/test/anytest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/anytest.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/anytest.cc > CMakeFiles/my_redies.dir/test/anytest.cc.i

CMakeFiles/my_redies.dir/test/anytest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/anytest.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/anytest.cc -o CMakeFiles/my_redies.dir/test/anytest.cc.s

CMakeFiles/my_redies.dir/test/test.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/test.cc.o: ../test/test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_redies.dir/test/test.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/test.cc.o -c /home/kiosk/CLionProjects/my_redies/test/test.cc

CMakeFiles/my_redies.dir/test/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/test.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/test.cc > CMakeFiles/my_redies.dir/test/test.cc.i

CMakeFiles/my_redies.dir/test/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/test.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/test.cc -o CMakeFiles/my_redies.dir/test/test.cc.s

CMakeFiles/my_redies.dir/test/random.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/random.cc.o: ../test/random.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_redies.dir/test/random.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/random.cc.o -c /home/kiosk/CLionProjects/my_redies/test/random.cc

CMakeFiles/my_redies.dir/test/random.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/random.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/random.cc > CMakeFiles/my_redies.dir/test/random.cc.i

CMakeFiles/my_redies.dir/test/random.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/random.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/random.cc -o CMakeFiles/my_redies.dir/test/random.cc.s

CMakeFiles/my_redies.dir/test/skiplisttest.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/skiplisttest.cc.o: ../test/skiplisttest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/my_redies.dir/test/skiplisttest.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/skiplisttest.cc.o -c /home/kiosk/CLionProjects/my_redies/test/skiplisttest.cc

CMakeFiles/my_redies.dir/test/skiplisttest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/skiplisttest.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/skiplisttest.cc > CMakeFiles/my_redies.dir/test/skiplisttest.cc.i

CMakeFiles/my_redies.dir/test/skiplisttest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/skiplisttest.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/skiplisttest.cc -o CMakeFiles/my_redies.dir/test/skiplisttest.cc.s

CMakeFiles/my_redies.dir/test/coding.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/coding.cc.o: ../test/coding.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/my_redies.dir/test/coding.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/coding.cc.o -c /home/kiosk/CLionProjects/my_redies/test/coding.cc

CMakeFiles/my_redies.dir/test/coding.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/coding.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/coding.cc > CMakeFiles/my_redies.dir/test/coding.cc.i

CMakeFiles/my_redies.dir/test/coding.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/coding.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/coding.cc -o CMakeFiles/my_redies.dir/test/coding.cc.s

CMakeFiles/my_redies.dir/test/bloom_test.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/bloom_test.cc.o: ../test/bloom_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/my_redies.dir/test/bloom_test.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/bloom_test.cc.o -c /home/kiosk/CLionProjects/my_redies/test/bloom_test.cc

CMakeFiles/my_redies.dir/test/bloom_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/bloom_test.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/bloom_test.cc > CMakeFiles/my_redies.dir/test/bloom_test.cc.i

CMakeFiles/my_redies.dir/test/bloom_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/bloom_test.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/bloom_test.cc -o CMakeFiles/my_redies.dir/test/bloom_test.cc.s

CMakeFiles/my_redies.dir/test/phmap.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/phmap.cc.o: ../test/phmap.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/my_redies.dir/test/phmap.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/phmap.cc.o -c /home/kiosk/CLionProjects/my_redies/test/phmap.cc

CMakeFiles/my_redies.dir/test/phmap.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/phmap.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/phmap.cc > CMakeFiles/my_redies.dir/test/phmap.cc.i

CMakeFiles/my_redies.dir/test/phmap.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/phmap.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/phmap.cc -o CMakeFiles/my_redies.dir/test/phmap.cc.s

CMakeFiles/my_redies.dir/base/dict_builder.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/base/dict_builder.cc.o: ../base/dict_builder.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/my_redies.dir/base/dict_builder.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/base/dict_builder.cc.o -c /home/kiosk/CLionProjects/my_redies/base/dict_builder.cc

CMakeFiles/my_redies.dir/base/dict_builder.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/base/dict_builder.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/base/dict_builder.cc > CMakeFiles/my_redies.dir/base/dict_builder.cc.i

CMakeFiles/my_redies.dir/base/dict_builder.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/base/dict_builder.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/base/dict_builder.cc -o CMakeFiles/my_redies.dir/base/dict_builder.cc.s

CMakeFiles/my_redies.dir/src/db_wr.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/src/db_wr.cc.o: ../src/db_wr.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/my_redies.dir/src/db_wr.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/src/db_wr.cc.o -c /home/kiosk/CLionProjects/my_redies/src/db_wr.cc

CMakeFiles/my_redies.dir/src/db_wr.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/src/db_wr.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/src/db_wr.cc > CMakeFiles/my_redies.dir/src/db_wr.cc.i

CMakeFiles/my_redies.dir/src/db_wr.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/src/db_wr.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/src/db_wr.cc -o CMakeFiles/my_redies.dir/src/db_wr.cc.s

CMakeFiles/my_redies.dir/test/do.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/do.cc.o: ../test/do.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/my_redies.dir/test/do.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/do.cc.o -c /home/kiosk/CLionProjects/my_redies/test/do.cc

CMakeFiles/my_redies.dir/test/do.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/do.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/do.cc > CMakeFiles/my_redies.dir/test/do.cc.i

CMakeFiles/my_redies.dir/test/do.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/do.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/do.cc -o CMakeFiles/my_redies.dir/test/do.cc.s

CMakeFiles/my_redies.dir/test/cache.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/test/cache.cc.o: ../test/cache.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/my_redies.dir/test/cache.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/test/cache.cc.o -c /home/kiosk/CLionProjects/my_redies/test/cache.cc

CMakeFiles/my_redies.dir/test/cache.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/test/cache.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/test/cache.cc > CMakeFiles/my_redies.dir/test/cache.cc.i

CMakeFiles/my_redies.dir/test/cache.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/test/cache.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/test/cache.cc -o CMakeFiles/my_redies.dir/test/cache.cc.s

CMakeFiles/my_redies.dir/src/snapshot.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/src/snapshot.cc.o: ../src/snapshot.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/my_redies.dir/src/snapshot.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/src/snapshot.cc.o -c /home/kiosk/CLionProjects/my_redies/src/snapshot.cc

CMakeFiles/my_redies.dir/src/snapshot.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/src/snapshot.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/src/snapshot.cc > CMakeFiles/my_redies.dir/src/snapshot.cc.i

CMakeFiles/my_redies.dir/src/snapshot.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/src/snapshot.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/src/snapshot.cc -o CMakeFiles/my_redies.dir/src/snapshot.cc.s

CMakeFiles/my_redies.dir/src/sstable.cc.o: CMakeFiles/my_redies.dir/flags.make
CMakeFiles/my_redies.dir/src/sstable.cc.o: ../src/sstable.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/my_redies.dir/src/sstable.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_redies.dir/src/sstable.cc.o -c /home/kiosk/CLionProjects/my_redies/src/sstable.cc

CMakeFiles/my_redies.dir/src/sstable.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_redies.dir/src/sstable.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiosk/CLionProjects/my_redies/src/sstable.cc > CMakeFiles/my_redies.dir/src/sstable.cc.i

CMakeFiles/my_redies.dir/src/sstable.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_redies.dir/src/sstable.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiosk/CLionProjects/my_redies/src/sstable.cc -o CMakeFiles/my_redies.dir/src/sstable.cc.s

# Object files for target my_redies
my_redies_OBJECTS = \
"CMakeFiles/my_redies.dir/main.cpp.o" \
"CMakeFiles/my_redies.dir/test/snappy.cc.o" \
"CMakeFiles/my_redies.dir/base/skiplist.cc.o" \
"CMakeFiles/my_redies.dir/util/Prena.cc.o" \
"CMakeFiles/my_redies.dir/test/anytest.cc.o" \
"CMakeFiles/my_redies.dir/test/test.cc.o" \
"CMakeFiles/my_redies.dir/test/random.cc.o" \
"CMakeFiles/my_redies.dir/test/skiplisttest.cc.o" \
"CMakeFiles/my_redies.dir/test/coding.cc.o" \
"CMakeFiles/my_redies.dir/test/bloom_test.cc.o" \
"CMakeFiles/my_redies.dir/test/phmap.cc.o" \
"CMakeFiles/my_redies.dir/base/dict_builder.cc.o" \
"CMakeFiles/my_redies.dir/src/db_wr.cc.o" \
"CMakeFiles/my_redies.dir/test/do.cc.o" \
"CMakeFiles/my_redies.dir/test/cache.cc.o" \
"CMakeFiles/my_redies.dir/src/snapshot.cc.o" \
"CMakeFiles/my_redies.dir/src/sstable.cc.o"

# External object files for target my_redies
my_redies_EXTERNAL_OBJECTS =

my_redies: CMakeFiles/my_redies.dir/main.cpp.o
my_redies: CMakeFiles/my_redies.dir/test/snappy.cc.o
my_redies: CMakeFiles/my_redies.dir/base/skiplist.cc.o
my_redies: CMakeFiles/my_redies.dir/util/Prena.cc.o
my_redies: CMakeFiles/my_redies.dir/test/anytest.cc.o
my_redies: CMakeFiles/my_redies.dir/test/test.cc.o
my_redies: CMakeFiles/my_redies.dir/test/random.cc.o
my_redies: CMakeFiles/my_redies.dir/test/skiplisttest.cc.o
my_redies: CMakeFiles/my_redies.dir/test/coding.cc.o
my_redies: CMakeFiles/my_redies.dir/test/bloom_test.cc.o
my_redies: CMakeFiles/my_redies.dir/test/phmap.cc.o
my_redies: CMakeFiles/my_redies.dir/base/dict_builder.cc.o
my_redies: CMakeFiles/my_redies.dir/src/db_wr.cc.o
my_redies: CMakeFiles/my_redies.dir/test/do.cc.o
my_redies: CMakeFiles/my_redies.dir/test/cache.cc.o
my_redies: CMakeFiles/my_redies.dir/src/snapshot.cc.o
my_redies: CMakeFiles/my_redies.dir/src/sstable.cc.o
my_redies: CMakeFiles/my_redies.dir/build.make
my_redies: CMakeFiles/my_redies.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable my_redies"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_redies.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_redies.dir/build: my_redies

.PHONY : CMakeFiles/my_redies.dir/build

CMakeFiles/my_redies.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_redies.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_redies.dir/clean

CMakeFiles/my_redies.dir/depend:
	cd /home/kiosk/CLionProjects/my_redies/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kiosk/CLionProjects/my_redies /home/kiosk/CLionProjects/my_redies /home/kiosk/CLionProjects/my_redies/cmake-build-debug /home/kiosk/CLionProjects/my_redies/cmake-build-debug /home/kiosk/CLionProjects/my_redies/cmake-build-debug/CMakeFiles/my_redies.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_redies.dir/depend

