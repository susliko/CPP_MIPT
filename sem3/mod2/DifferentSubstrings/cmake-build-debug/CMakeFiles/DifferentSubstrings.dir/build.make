# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/susliko/IDES/clion-2017.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/susliko/IDES/clion-2017.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DifferentSubstrings.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DifferentSubstrings.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DifferentSubstrings.dir/flags.make

CMakeFiles/DifferentSubstrings.dir/main.cpp.o: CMakeFiles/DifferentSubstrings.dir/flags.make
CMakeFiles/DifferentSubstrings.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DifferentSubstrings.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DifferentSubstrings.dir/main.cpp.o -c /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/main.cpp

CMakeFiles/DifferentSubstrings.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DifferentSubstrings.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/main.cpp > CMakeFiles/DifferentSubstrings.dir/main.cpp.i

CMakeFiles/DifferentSubstrings.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DifferentSubstrings.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/main.cpp -o CMakeFiles/DifferentSubstrings.dir/main.cpp.s

CMakeFiles/DifferentSubstrings.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/DifferentSubstrings.dir/main.cpp.o.requires

CMakeFiles/DifferentSubstrings.dir/main.cpp.o.provides: CMakeFiles/DifferentSubstrings.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/DifferentSubstrings.dir/build.make CMakeFiles/DifferentSubstrings.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/DifferentSubstrings.dir/main.cpp.o.provides

CMakeFiles/DifferentSubstrings.dir/main.cpp.o.provides.build: CMakeFiles/DifferentSubstrings.dir/main.cpp.o


# Object files for target DifferentSubstrings
DifferentSubstrings_OBJECTS = \
"CMakeFiles/DifferentSubstrings.dir/main.cpp.o"

# External object files for target DifferentSubstrings
DifferentSubstrings_EXTERNAL_OBJECTS =

DifferentSubstrings: CMakeFiles/DifferentSubstrings.dir/main.cpp.o
DifferentSubstrings: CMakeFiles/DifferentSubstrings.dir/build.make
DifferentSubstrings: CMakeFiles/DifferentSubstrings.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DifferentSubstrings"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DifferentSubstrings.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DifferentSubstrings.dir/build: DifferentSubstrings

.PHONY : CMakeFiles/DifferentSubstrings.dir/build

CMakeFiles/DifferentSubstrings.dir/requires: CMakeFiles/DifferentSubstrings.dir/main.cpp.o.requires

.PHONY : CMakeFiles/DifferentSubstrings.dir/requires

CMakeFiles/DifferentSubstrings.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DifferentSubstrings.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DifferentSubstrings.dir/clean

CMakeFiles/DifferentSubstrings.dir/depend:
	cd /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/cmake-build-debug /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/cmake-build-debug /home/susliko/IDES/CLionProjects/CPP_MIPT/sem3/mod2/DifferentSubstrings/cmake-build-debug/CMakeFiles/DifferentSubstrings.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DifferentSubstrings.dir/depend

