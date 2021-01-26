cmake_minimum_required(VERSION 3.13)
project(proj_1_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj_1_
        .idea/.name
        .idea/encodings.xml
        .idea/misc.xml
        .idea/modules.xml
        ".idea/proj(1).iml"
        .idea/workspace.xml
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/proj
        cmake-build-debug/proj.cbp
        cmake-build-debug/tabuleiro.txt
        CMakeLists.txt
        estado.c
        estado.h
        main.c)
