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
CMAKE_SOURCE_DIR = /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin/build

# Utility rule file for ModelPlugin_autogen.

# Include the progress variables for this target.
include CMakeFiles/ModelPlugin_autogen.dir/progress.make

CMakeFiles/ModelPlugin_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target ModelPlugin"
	/usr/bin/cmake -E cmake_autogen /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin/build/CMakeFiles/ModelPlugin_autogen.dir/AutogenInfo.json ""

ModelPlugin_autogen: CMakeFiles/ModelPlugin_autogen
ModelPlugin_autogen: CMakeFiles/ModelPlugin_autogen.dir/build.make

.PHONY : ModelPlugin_autogen

# Rule to build all files generated by this target.
CMakeFiles/ModelPlugin_autogen.dir/build: ModelPlugin_autogen

.PHONY : CMakeFiles/ModelPlugin_autogen.dir/build

CMakeFiles/ModelPlugin_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ModelPlugin_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ModelPlugin_autogen.dir/clean

CMakeFiles/ModelPlugin_autogen.dir/depend:
	cd /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin/build /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin/build /home/seraphym/Programming/Luxoft/Match3/Plugins/ModelPlugin/build/CMakeFiles/ModelPlugin_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ModelPlugin_autogen.dir/depend
