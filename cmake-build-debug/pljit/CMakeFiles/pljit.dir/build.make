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
CMAKE_COMMAND = /home/wuha/Clion/clion-2020.1.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/wuha/Clion/clion-2020.1.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug"

# Include any dependencies generated for this target.
include pljit/CMakeFiles/pljit.dir/depend.make

# Include the progress variables for this target.
include pljit/CMakeFiles/pljit.dir/progress.make

# Include the compile flags for this target's objects.
include pljit/CMakeFiles/pljit.dir/flags.make

pljit/CMakeFiles/pljit.dir/main.cpp.o: pljit/CMakeFiles/pljit.dir/flags.make
pljit/CMakeFiles/pljit.dir/main.cpp.o: ../pljit/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pljit/CMakeFiles/pljit.dir/main.cpp.o"
	cd "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/pljit" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pljit.dir/main.cpp.o -c "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/pljit/main.cpp"

pljit/CMakeFiles/pljit.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pljit.dir/main.cpp.i"
	cd "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/pljit" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/pljit/main.cpp" > CMakeFiles/pljit.dir/main.cpp.i

pljit/CMakeFiles/pljit.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pljit.dir/main.cpp.s"
	cd "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/pljit" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/pljit/main.cpp" -o CMakeFiles/pljit.dir/main.cpp.s

# Object files for target pljit
pljit_OBJECTS = \
"CMakeFiles/pljit.dir/main.cpp.o"

# External object files for target pljit
pljit_EXTERNAL_OBJECTS =

pljit/pljit: pljit/CMakeFiles/pljit.dir/main.cpp.o
pljit/pljit: pljit/CMakeFiles/pljit.dir/build.make
pljit/pljit: pljit/libpljit_core.a
pljit/pljit: pljit/CMakeFiles/pljit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pljit"
	cd "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/pljit" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pljit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pljit/CMakeFiles/pljit.dir/build: pljit/pljit

.PHONY : pljit/CMakeFiles/pljit.dir/build

pljit/CMakeFiles/pljit.dir/clean:
	cd "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/pljit" && $(CMAKE_COMMAND) -P CMakeFiles/pljit.dir/cmake_clean.cmake
.PHONY : pljit/CMakeFiles/pljit.dir/clean

pljit/CMakeFiles/pljit.dir/depend:
	cd "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final" "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/pljit" "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug" "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/pljit" "/home/wuha/Wu Hanfeng/TUM/cpppraktikum/New Folder/final/cmake-build-debug/pljit/CMakeFiles/pljit.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : pljit/CMakeFiles/pljit.dir/depend

