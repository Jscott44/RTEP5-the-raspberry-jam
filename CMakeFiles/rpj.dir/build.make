# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/repos/RTEP5-the-raspberry-jam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/repos/RTEP5-the-raspberry-jam

# Include any dependencies generated for this target.
include CMakeFiles/rpj.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rpj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rpj.dir/flags.make

CMakeFiles/rpj.dir/main.cpp.o: CMakeFiles/rpj.dir/flags.make
CMakeFiles/rpj.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/repos/RTEP5-the-raspberry-jam/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rpj.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpj.dir/main.cpp.o -c /home/user/repos/RTEP5-the-raspberry-jam/main.cpp

CMakeFiles/rpj.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpj.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/repos/RTEP5-the-raspberry-jam/main.cpp > CMakeFiles/rpj.dir/main.cpp.i

CMakeFiles/rpj.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpj.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/repos/RTEP5-the-raspberry-jam/main.cpp -o CMakeFiles/rpj.dir/main.cpp.s

# Object files for target rpj
rpj_OBJECTS = \
"CMakeFiles/rpj.dir/main.cpp.o"

# External object files for target rpj
rpj_EXTERNAL_OBJECTS =

rpj: CMakeFiles/rpj.dir/main.cpp.o
rpj: CMakeFiles/rpj.dir/build.make
rpj: /usr/lib/x86_64-linux-gnu/libasound.so
rpj: AlsaEffects/libAlsaEffects.a
rpj: CMakeFiles/rpj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/repos/RTEP5-the-raspberry-jam/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rpj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rpj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rpj.dir/build: rpj

.PHONY : CMakeFiles/rpj.dir/build

CMakeFiles/rpj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rpj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rpj.dir/clean

CMakeFiles/rpj.dir/depend:
	cd /home/user/repos/RTEP5-the-raspberry-jam && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/repos/RTEP5-the-raspberry-jam /home/user/repos/RTEP5-the-raspberry-jam /home/user/repos/RTEP5-the-raspberry-jam /home/user/repos/RTEP5-the-raspberry-jam /home/user/repos/RTEP5-the-raspberry-jam/CMakeFiles/rpj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rpj.dir/depend

