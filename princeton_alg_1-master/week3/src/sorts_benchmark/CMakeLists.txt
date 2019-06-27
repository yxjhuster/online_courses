cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-g -std=c++11")

set(HDR_LIST src/sort.h)

set(SRC_LIST src/main.cpp)

add_executable(app ${HDR_LIST} ${SRC_LIST})

#add_subdirectory(tests)

