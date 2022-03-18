
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD "20")
project(forMatcher)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib)
