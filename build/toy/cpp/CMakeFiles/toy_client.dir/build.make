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
include toy/cpp/CMakeFiles/toy_client.dir/depend.make

# Include the progress variables for this target.
include toy/cpp/CMakeFiles/toy_client.dir/progress.make

# Include the compile flags for this target's objects.
include toy/cpp/CMakeFiles/toy_client.dir/flags.make

toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj: toy/cpp/CMakeFiles/toy_client.dir/flags.make
toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj: ../toy/cpp/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\work\engine\rabbit_server\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj"
	cd /d E:\work\engine\rabbit_server\build\toy\cpp && C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\toy_client.dir\client.cpp.obj -c E:\work\engine\rabbit_server\toy\cpp\client.cpp

toy/cpp/CMakeFiles/toy_client.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/toy_client.dir/client.cpp.i"
	cd /d E:\work\engine\rabbit_server\build\toy\cpp && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E E:\work\engine\rabbit_server\toy\cpp\client.cpp > CMakeFiles\toy_client.dir\client.cpp.i

toy/cpp/CMakeFiles/toy_client.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/toy_client.dir/client.cpp.s"
	cd /d E:\work\engine\rabbit_server\build\toy\cpp && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S E:\work\engine\rabbit_server\toy\cpp\client.cpp -o CMakeFiles\toy_client.dir\client.cpp.s

toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.requires:

.PHONY : toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.requires

toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.provides: toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.requires
	$(MAKE) -f toy\cpp\CMakeFiles\toy_client.dir\build.make toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.provides.build
.PHONY : toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.provides

toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.provides.build: toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj


# Object files for target toy_client
toy_client_OBJECTS = \
"CMakeFiles/toy_client.dir/client.cpp.obj"

# External object files for target toy_client
toy_client_EXTERNAL_OBJECTS =

toy/cpp/toy_client.exe: toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj
toy/cpp/toy_client.exe: toy/cpp/CMakeFiles/toy_client.dir/build.make
toy/cpp/toy_client.exe: toy/cpp/CMakeFiles/toy_client.dir/objects1.rsp
toy/cpp/toy_client.exe: toy/cpp/CMakeFiles/toy_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\work\engine\rabbit_server\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable toy_client.exe"
	cd /d E:\work\engine\rabbit_server\build\toy\cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\toy_client.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
toy/cpp/CMakeFiles/toy_client.dir/build: toy/cpp/toy_client.exe

.PHONY : toy/cpp/CMakeFiles/toy_client.dir/build

toy/cpp/CMakeFiles/toy_client.dir/requires: toy/cpp/CMakeFiles/toy_client.dir/client.cpp.obj.requires

.PHONY : toy/cpp/CMakeFiles/toy_client.dir/requires

toy/cpp/CMakeFiles/toy_client.dir/clean:
	cd /d E:\work\engine\rabbit_server\build\toy\cpp && $(CMAKE_COMMAND) -P CMakeFiles\toy_client.dir\cmake_clean.cmake
.PHONY : toy/cpp/CMakeFiles/toy_client.dir/clean

toy/cpp/CMakeFiles/toy_client.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\work\engine\rabbit_server E:\work\engine\rabbit_server\toy\cpp E:\work\engine\rabbit_server\build E:\work\engine\rabbit_server\build\toy\cpp E:\work\engine\rabbit_server\build\toy\cpp\CMakeFiles\toy_client.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : toy/cpp/CMakeFiles/toy_client.dir/depend

