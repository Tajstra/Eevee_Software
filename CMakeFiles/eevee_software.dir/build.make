# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Tools\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\Tools\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Software\Eevee_Software

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Software\Eevee_Software

# Include any dependencies generated for this target.
include CMakeFiles/eevee_software.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/eevee_software.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/eevee_software.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eevee_software.dir/flags.make

CMakeFiles/eevee_software.dir/test/test.cpp.obj: CMakeFiles/eevee_software.dir/flags.make
CMakeFiles/eevee_software.dir/test/test.cpp.obj: test/test.cpp
CMakeFiles/eevee_software.dir/test/test.cpp.obj: CMakeFiles/eevee_software.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Software\Eevee_Software\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/eevee_software.dir/test/test.cpp.obj"
	C:\Tools\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/eevee_software.dir/test/test.cpp.obj -MF CMakeFiles\eevee_software.dir\test\test.cpp.obj.d -o CMakeFiles\eevee_software.dir\test\test.cpp.obj -c E:\Software\Eevee_Software\test\test.cpp

CMakeFiles/eevee_software.dir/test/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eevee_software.dir/test/test.cpp.i"
	C:\Tools\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Software\Eevee_Software\test\test.cpp > CMakeFiles\eevee_software.dir\test\test.cpp.i

CMakeFiles/eevee_software.dir/test/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eevee_software.dir/test/test.cpp.s"
	C:\Tools\msys64\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Software\Eevee_Software\test\test.cpp -o CMakeFiles\eevee_software.dir\test\test.cpp.s

# Object files for target eevee_software
eevee_software_OBJECTS = \
"CMakeFiles/eevee_software.dir/test/test.cpp.obj"

# External object files for target eevee_software
eevee_software_EXTERNAL_OBJECTS =

eevee_software.exe: CMakeFiles/eevee_software.dir/test/test.cpp.obj
eevee_software.exe: CMakeFiles/eevee_software.dir/build.make
eevee_software.exe: CMakeFiles/eevee_software.dir/linklibs.rsp
eevee_software.exe: CMakeFiles/eevee_software.dir/objects1.rsp
eevee_software.exe: CMakeFiles/eevee_software.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Software\Eevee_Software\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable eevee_software.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\eevee_software.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eevee_software.dir/build: eevee_software.exe
.PHONY : CMakeFiles/eevee_software.dir/build

CMakeFiles/eevee_software.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\eevee_software.dir\cmake_clean.cmake
.PHONY : CMakeFiles/eevee_software.dir/clean

CMakeFiles/eevee_software.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Software\Eevee_Software E:\Software\Eevee_Software E:\Software\Eevee_Software E:\Software\Eevee_Software E:\Software\Eevee_Software\CMakeFiles\eevee_software.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eevee_software.dir/depend

