# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/qrstu/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/qrstu/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/qrstu/yty_folder2/OBCompetition

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/qrstu/yty_folder2/OBCompetition/build

# Include any dependencies generated for this target.
include test/CMakeFiles/client_performance_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/client_performance_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/client_performance_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/client_performance_test.dir/flags.make

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: test/CMakeFiles/client_performance_test.dir/flags.make
test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: ../test/client_performance_test.cpp
test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o: test/CMakeFiles/client_performance_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qrstu/yty_folder2/OBCompetition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o"
	cd /home/qrstu/yty_folder2/OBCompetition/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o -MF CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o.d -o CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o -c /home/qrstu/yty_folder2/OBCompetition/test/client_performance_test.cpp

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i"
	cd /home/qrstu/yty_folder2/OBCompetition/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qrstu/yty_folder2/OBCompetition/test/client_performance_test.cpp > CMakeFiles/client_performance_test.dir/client_performance_test.cpp.i

test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s"
	cd /home/qrstu/yty_folder2/OBCompetition/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qrstu/yty_folder2/OBCompetition/test/client_performance_test.cpp -o CMakeFiles/client_performance_test.dir/client_performance_test.cpp.s

# Object files for target client_performance_test
client_performance_test_OBJECTS = \
"CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o"

# External object files for target client_performance_test
client_performance_test_EXTERNAL_OBJECTS =

bin/client_performance_test: test/CMakeFiles/client_performance_test.dir/client_performance_test.cpp.o
bin/client_performance_test: test/CMakeFiles/client_performance_test.dir/build.make
bin/client_performance_test: lib/libobserver.a
bin/client_performance_test: lib/libcommon.so.1.0.0
bin/client_performance_test: test/CMakeFiles/client_performance_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/qrstu/yty_folder2/OBCompetition/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/client_performance_test"
	cd /home/qrstu/yty_folder2/OBCompetition/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_performance_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/client_performance_test.dir/build: bin/client_performance_test
.PHONY : test/CMakeFiles/client_performance_test.dir/build

test/CMakeFiles/client_performance_test.dir/clean:
	cd /home/qrstu/yty_folder2/OBCompetition/build/test && $(CMAKE_COMMAND) -P CMakeFiles/client_performance_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/client_performance_test.dir/clean

test/CMakeFiles/client_performance_test.dir/depend:
	cd /home/qrstu/yty_folder2/OBCompetition/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/qrstu/yty_folder2/OBCompetition /home/qrstu/yty_folder2/OBCompetition/test /home/qrstu/yty_folder2/OBCompetition/build /home/qrstu/yty_folder2/OBCompetition/build/test /home/qrstu/yty_folder2/OBCompetition/build/test/CMakeFiles/client_performance_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/client_performance_test.dir/depend

