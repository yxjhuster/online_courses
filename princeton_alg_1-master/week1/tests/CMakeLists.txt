cmake_minimum_required(VERSION 2.8)

enable_testing(true)
add_subdirectory(/home/vram/lib/googletest/googletest/ ./gtest)
include_directories(src ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(APP_SRC_LIST ../app/quick_union.cpp
                 ../app/percolation.cpp)
set(TEST_SRC_LIST quick_union_tests.cpp
                  unit_tests.cpp
                  percolation_tests.cpp)
include_directories(../app)

add_executable(unit_tests ${APP_SRC_LIST} ${TEST_SRC_LIST})
target_link_libraries(unit_tests gtest gtest_main)

