cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(HDR_LIST app/quick_union.h
             app/percolation.h)
set(SRC_LIST app/quick_union.cpp
             app/percolation.cpp
             app/main.cpp)

add_executable(app ${HDR_LIST} ${SRC_LIST})

add_subdirectory(tests)
