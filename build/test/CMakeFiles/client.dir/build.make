# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.3

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\work\engine\rabbit_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\work\engine\rabbit_server\build

# Include any dependencies generated for this target.
include test/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/client.dir/flags.make

test/CMakeFiles/client.dir/client.cpp.obj: test/CMakeFiles/client.dir/flags.make
test/CMakeFiles/client.dir/client.cpp.obj: ../test/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\work\engine\rabbit_server\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/client.dir/client.cpp.obj"
	cd /d E:\work\engine\rabbit_server\build\test && C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\client.dir\client.cpp.obj -c E:\work\engine\rabbit_server\test\client.cpp

test/CMakeFiles/client.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client.cpp.i"
	cd /d E:\work\engine\rabbit_server\build\test && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E E:\work\engine\rabbit_server\test\client.cpp > CMakeFiles\client.dir\client.cpp.i

test/CMakeFiles/client.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client.cpp.s"
	cd /d E:\work\engine\rabbit_server\build\test && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S E:\work\engine\rabbit_server\test\client.cpp -o CMakeFiles\client.dir\client.cpp.s

test/CMakeFiles/client.dir/client.cpp.obj.requires:

.PHONY : test/CMakeFiles/client.dir/client.cpp.obj.requires

test/CMakeFiles/client.dir/client.cpp.obj.provides: test/CMakeFiles/client.dir/client.cpp.obj.requires
	$(MAKE) -f test\CMakeFiles\client.dir\build.make test/CMakeFiles/client.dir/client.cpp.obj.provides.build
.PHONY : test/CMakeFiles/client.dir/client.cpp.obj.provides

test/CMakeFiles/client.dir/client.cpp.obj.provides.build: test/CMakeFiles/client.dir/client.cpp.obj


# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client.cpp.obj"

# External object files for target client
client_EXTERNAL_OBJECTS =

test/client.exe: test/CMakeFiles/client.dir/client.cpp.obj
test/client.exe: test/CMakeFiles/client.dir/build.make
test/client.exe: src/libserver_lib.a
test/client.exe: test/CMakeFiles/client.dir/objects1.rsp
test/client.exe: test/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\work\engine\rabbit_server\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable client.exe"
	cd /d E:\work\engine\rabbit_server\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\client.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/client.dir/build: test/client.exe

.PHONY : test/CMakeFiles/client.dir/build

test/CMakeFiles/client.dir/requires: test/CMakeFiles/client.dir/client.cpp.obj.requires

.PHONY : test/CMakeFiles/client.dir/requires

test/CMakeFiles/client.dir/clean:
	cd /d E:\work\engine\rabbit_server\build\test && $(CMAKE_COMMAND) -P CMakeFiles\client.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/client.dir/clean

test/CMakeFiles/client.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\work\engine\rabbit_server E:\work\engine\rabbit_server\test E:\work\engine\rabbit_server\build E:\work\engine\rabbit_server\build\test E:\work\engine\rabbit_server\build\test\CMakeFiles\client.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/client.dir/depend

