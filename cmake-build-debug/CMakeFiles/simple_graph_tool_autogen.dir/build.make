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
CMAKE_COMMAND = /snap/clion/114/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/114/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/haophancs/Projects/Qt/simple-graph-tool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/haophancs/Projects/Qt/simple-graph-tool/cmake-build-debug

# Utility rule file for simple_graph_tool_autogen.

# Include the progress variables for this target.
include CMakeFiles/simple_graph_tool_autogen.dir/progress.make

CMakeFiles/simple_graph_tool_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/haophancs/Projects/Qt/simple-graph-tool/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target simple_graph_tool"
	/snap/clion/114/bin/cmake/linux/bin/cmake -E cmake_autogen /home/haophancs/Projects/Qt/simple-graph-tool/cmake-build-debug/CMakeFiles/simple_graph_tool_autogen.dir/AutogenInfo.json Debug

simple_graph_tool_autogen: CMakeFiles/simple_graph_tool_autogen
simple_graph_tool_autogen: CMakeFiles/simple_graph_tool_autogen.dir/build.make

.PHONY : simple_graph_tool_autogen

# Rule to build all files generated by this target.
CMakeFiles/simple_graph_tool_autogen.dir/build: simple_graph_tool_autogen

.PHONY : CMakeFiles/simple_graph_tool_autogen.dir/build

CMakeFiles/simple_graph_tool_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simple_graph_tool_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simple_graph_tool_autogen.dir/clean

CMakeFiles/simple_graph_tool_autogen.dir/depend:
	cd /home/haophancs/Projects/Qt/simple-graph-tool/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/haophancs/Projects/Qt/simple-graph-tool /home/haophancs/Projects/Qt/simple-graph-tool /home/haophancs/Projects/Qt/simple-graph-tool/cmake-build-debug /home/haophancs/Projects/Qt/simple-graph-tool/cmake-build-debug /home/haophancs/Projects/Qt/simple-graph-tool/cmake-build-debug/CMakeFiles/simple_graph_tool_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simple_graph_tool_autogen.dir/depend
