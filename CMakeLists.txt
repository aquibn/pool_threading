cmake_minimum_required(VERSION 3.10)

# Set project name and language
project(ThreadPoolExample CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory
include_directories(include)

# Add source files
add_executable(ThreadPoolExample src/main.cpp src/ThreadPool.cpp)

# Optional: Add tests if you want to later integrate testing frameworks like GoogleTest
# add_executable(thread_pool_tests tests/test_thread_pool.cpp)
# target_link_libraries(thread_pool_tests gtest gtest_main)
