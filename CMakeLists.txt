project(podo)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "-g -Wall -O2 -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "-g -Wall -O2 -fno-omit-frame-pointer")

add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(examples)

