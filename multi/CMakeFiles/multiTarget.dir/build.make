# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/eric/Desktop/flightCode/multi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eric/Desktop/flightCode/multi

# Include any dependencies generated for this target.
include CMakeFiles/multiTarget.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multiTarget.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multiTarget.dir/flags.make

CMakeFiles/multiTarget.dir/multiTracking.cpp.o: CMakeFiles/multiTarget.dir/flags.make
CMakeFiles/multiTarget.dir/multiTracking.cpp.o: multiTracking.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/Desktop/flightCode/multi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multiTarget.dir/multiTracking.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multiTarget.dir/multiTracking.cpp.o -c /home/eric/Desktop/flightCode/multi/multiTracking.cpp

CMakeFiles/multiTarget.dir/multiTracking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multiTarget.dir/multiTracking.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/Desktop/flightCode/multi/multiTracking.cpp > CMakeFiles/multiTarget.dir/multiTracking.cpp.i

CMakeFiles/multiTarget.dir/multiTracking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multiTarget.dir/multiTracking.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/Desktop/flightCode/multi/multiTracking.cpp -o CMakeFiles/multiTarget.dir/multiTracking.cpp.s

CMakeFiles/multiTarget.dir/multiTracking.cpp.o.requires:

.PHONY : CMakeFiles/multiTarget.dir/multiTracking.cpp.o.requires

CMakeFiles/multiTarget.dir/multiTracking.cpp.o.provides: CMakeFiles/multiTarget.dir/multiTracking.cpp.o.requires
	$(MAKE) -f CMakeFiles/multiTarget.dir/build.make CMakeFiles/multiTarget.dir/multiTracking.cpp.o.provides.build
.PHONY : CMakeFiles/multiTarget.dir/multiTracking.cpp.o.provides

CMakeFiles/multiTarget.dir/multiTracking.cpp.o.provides.build: CMakeFiles/multiTarget.dir/multiTracking.cpp.o


CMakeFiles/multiTarget.dir/Roomba.cpp.o: CMakeFiles/multiTarget.dir/flags.make
CMakeFiles/multiTarget.dir/Roomba.cpp.o: Roomba.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/Desktop/flightCode/multi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/multiTarget.dir/Roomba.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multiTarget.dir/Roomba.cpp.o -c /home/eric/Desktop/flightCode/multi/Roomba.cpp

CMakeFiles/multiTarget.dir/Roomba.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multiTarget.dir/Roomba.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/Desktop/flightCode/multi/Roomba.cpp > CMakeFiles/multiTarget.dir/Roomba.cpp.i

CMakeFiles/multiTarget.dir/Roomba.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multiTarget.dir/Roomba.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/Desktop/flightCode/multi/Roomba.cpp -o CMakeFiles/multiTarget.dir/Roomba.cpp.s

CMakeFiles/multiTarget.dir/Roomba.cpp.o.requires:

.PHONY : CMakeFiles/multiTarget.dir/Roomba.cpp.o.requires

CMakeFiles/multiTarget.dir/Roomba.cpp.o.provides: CMakeFiles/multiTarget.dir/Roomba.cpp.o.requires
	$(MAKE) -f CMakeFiles/multiTarget.dir/build.make CMakeFiles/multiTarget.dir/Roomba.cpp.o.provides.build
.PHONY : CMakeFiles/multiTarget.dir/Roomba.cpp.o.provides

CMakeFiles/multiTarget.dir/Roomba.cpp.o.provides.build: CMakeFiles/multiTarget.dir/Roomba.cpp.o


# Object files for target multiTarget
multiTarget_OBJECTS = \
"CMakeFiles/multiTarget.dir/multiTracking.cpp.o" \
"CMakeFiles/multiTarget.dir/Roomba.cpp.o"

# External object files for target multiTarget
multiTarget_EXTERNAL_OBJECTS =

multiTarget: CMakeFiles/multiTarget.dir/multiTracking.cpp.o
multiTarget: CMakeFiles/multiTarget.dir/Roomba.cpp.o
multiTarget: CMakeFiles/multiTarget.dir/build.make
multiTarget: /usr/local/lib/libopencv_ml.so.3.2.0
multiTarget: /usr/local/lib/libopencv_objdetect.so.3.2.0
multiTarget: /usr/local/lib/libopencv_shape.so.3.2.0
multiTarget: /usr/local/lib/libopencv_stitching.so.3.2.0
multiTarget: /usr/local/lib/libopencv_superres.so.3.2.0
multiTarget: /usr/local/lib/libopencv_videostab.so.3.2.0
multiTarget: /usr/local/lib/libopencv_calib3d.so.3.2.0
multiTarget: /usr/local/lib/libopencv_features2d.so.3.2.0
multiTarget: /usr/local/lib/libopencv_flann.so.3.2.0
multiTarget: /usr/local/lib/libopencv_highgui.so.3.2.0
multiTarget: /usr/local/lib/libopencv_photo.so.3.2.0
multiTarget: /usr/local/lib/libopencv_video.so.3.2.0
multiTarget: /usr/local/lib/libopencv_videoio.so.3.2.0
multiTarget: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
multiTarget: /usr/local/lib/libopencv_imgproc.so.3.2.0
multiTarget: /usr/local/lib/libopencv_core.so.3.2.0
multiTarget: CMakeFiles/multiTarget.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eric/Desktop/flightCode/multi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable multiTarget"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multiTarget.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multiTarget.dir/build: multiTarget

.PHONY : CMakeFiles/multiTarget.dir/build

CMakeFiles/multiTarget.dir/requires: CMakeFiles/multiTarget.dir/multiTracking.cpp.o.requires
CMakeFiles/multiTarget.dir/requires: CMakeFiles/multiTarget.dir/Roomba.cpp.o.requires

.PHONY : CMakeFiles/multiTarget.dir/requires

CMakeFiles/multiTarget.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multiTarget.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multiTarget.dir/clean

CMakeFiles/multiTarget.dir/depend:
	cd /home/eric/Desktop/flightCode/multi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eric/Desktop/flightCode/multi /home/eric/Desktop/flightCode/multi /home/eric/Desktop/flightCode/multi /home/eric/Desktop/flightCode/multi /home/eric/Desktop/flightCode/multi/CMakeFiles/multiTarget.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multiTarget.dir/depend

