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
CMAKE_SOURCE_DIR = /home/ronnoc/CPDProgram/CPD_TimeShifter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ronnoc/CPDProgram/CPD_TimeShifter

# Utility rule file for TimeShifter_autogen.

# Include the progress variables for this target.
include CMakeFiles/TimeShifter_autogen.dir/progress.make

CMakeFiles/TimeShifter_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ronnoc/CPDProgram/CPD_TimeShifter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target TimeShifter"
	/usr/bin/cmake -E cmake_autogen /home/ronnoc/CPDProgram/CPD_TimeShifter/CMakeFiles/TimeShifter_autogen.dir/AutogenInfo.json ""

TimeShifter_autogen: CMakeFiles/TimeShifter_autogen
TimeShifter_autogen: CMakeFiles/TimeShifter_autogen.dir/build.make

.PHONY : TimeShifter_autogen

# Rule to build all files generated by this target.
CMakeFiles/TimeShifter_autogen.dir/build: TimeShifter_autogen

.PHONY : CMakeFiles/TimeShifter_autogen.dir/build

CMakeFiles/TimeShifter_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TimeShifter_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TimeShifter_autogen.dir/clean

CMakeFiles/TimeShifter_autogen.dir/depend:
	cd /home/ronnoc/CPDProgram/CPD_TimeShifter && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ronnoc/CPDProgram/CPD_TimeShifter /home/ronnoc/CPDProgram/CPD_TimeShifter /home/ronnoc/CPDProgram/CPD_TimeShifter /home/ronnoc/CPDProgram/CPD_TimeShifter /home/ronnoc/CPDProgram/CPD_TimeShifter/CMakeFiles/TimeShifter_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TimeShifter_autogen.dir/depend

