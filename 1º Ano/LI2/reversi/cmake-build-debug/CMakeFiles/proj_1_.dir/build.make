# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\g1nog\Desktop\bikes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\g1nog\Desktop\bikes\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proj_1_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proj_1_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proj_1_.dir/flags.make

CMakeFiles/proj_1_.dir/estado.c.obj: CMakeFiles/proj_1_.dir/flags.make
CMakeFiles/proj_1_.dir/estado.c.obj: CMakeFiles/proj_1_.dir/includes_C.rsp
CMakeFiles/proj_1_.dir/estado.c.obj: ../estado.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\g1nog\Desktop\bikes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/proj_1_.dir/estado.c.obj"
	C:\PROGRA~1\HASKEL~1\826561~1.1\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\proj_1_.dir\estado.c.obj   -c C:\Users\g1nog\Desktop\bikes\estado.c

CMakeFiles/proj_1_.dir/estado.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proj_1_.dir/estado.c.i"
	C:\PROGRA~1\HASKEL~1\826561~1.1\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\g1nog\Desktop\bikes\estado.c > CMakeFiles\proj_1_.dir\estado.c.i

CMakeFiles/proj_1_.dir/estado.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proj_1_.dir/estado.c.s"
	C:\PROGRA~1\HASKEL~1\826561~1.1\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\g1nog\Desktop\bikes\estado.c -o CMakeFiles\proj_1_.dir\estado.c.s

CMakeFiles/proj_1_.dir/main.c.obj: CMakeFiles/proj_1_.dir/flags.make
CMakeFiles/proj_1_.dir/main.c.obj: CMakeFiles/proj_1_.dir/includes_C.rsp
CMakeFiles/proj_1_.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\g1nog\Desktop\bikes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/proj_1_.dir/main.c.obj"
	C:\PROGRA~1\HASKEL~1\826561~1.1\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\proj_1_.dir\main.c.obj   -c C:\Users\g1nog\Desktop\bikes\main.c

CMakeFiles/proj_1_.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proj_1_.dir/main.c.i"
	C:\PROGRA~1\HASKEL~1\826561~1.1\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\g1nog\Desktop\bikes\main.c > CMakeFiles\proj_1_.dir\main.c.i

CMakeFiles/proj_1_.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proj_1_.dir/main.c.s"
	C:\PROGRA~1\HASKEL~1\826561~1.1\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\g1nog\Desktop\bikes\main.c -o CMakeFiles\proj_1_.dir\main.c.s

# Object files for target proj_1_
proj_1__OBJECTS = \
"CMakeFiles/proj_1_.dir/estado.c.obj" \
"CMakeFiles/proj_1_.dir/main.c.obj"

# External object files for target proj_1_
proj_1__EXTERNAL_OBJECTS =

proj_1_.exe: CMakeFiles/proj_1_.dir/estado.c.obj
proj_1_.exe: CMakeFiles/proj_1_.dir/main.c.obj
proj_1_.exe: CMakeFiles/proj_1_.dir/build.make
proj_1_.exe: CMakeFiles/proj_1_.dir/linklibs.rsp
proj_1_.exe: CMakeFiles/proj_1_.dir/objects1.rsp
proj_1_.exe: CMakeFiles/proj_1_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\g1nog\Desktop\bikes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable proj_1_.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\proj_1_.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proj_1_.dir/build: proj_1_.exe

.PHONY : CMakeFiles/proj_1_.dir/build

CMakeFiles/proj_1_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\proj_1_.dir\cmake_clean.cmake
.PHONY : CMakeFiles/proj_1_.dir/clean

CMakeFiles/proj_1_.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\g1nog\Desktop\bikes C:\Users\g1nog\Desktop\bikes C:\Users\g1nog\Desktop\bikes\cmake-build-debug C:\Users\g1nog\Desktop\bikes\cmake-build-debug C:\Users\g1nog\Desktop\bikes\cmake-build-debug\CMakeFiles\proj_1_.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proj_1_.dir/depend

