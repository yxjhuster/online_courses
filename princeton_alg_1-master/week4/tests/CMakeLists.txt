cmake_minimum_required(VERSION 2.8)

add_subdirectory(/home/vram/lib/googletest/googletest/ ./gtest)
include_directories(src ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(APP_SRC_LIST )

set(TEST_SRC_LIST unit_tests.cpp heap_tests.cpp)

add_executable(unit_tests ${APP_SRC_LIST} ${TEST_SRC_LIST})
target_link_libraries(unit_tests gtest gtest_main)

