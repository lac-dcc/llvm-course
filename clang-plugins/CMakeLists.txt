# Usage
# mkdir build
# cd build
# cmake ../ -DLLVM_DIR=${LLVM_BUILD_DIR}/lib/cmake/llvm -DClang_DIR=${LLVM_BUILD_DIR}/lib/cmake/clang
# make

cmake_minimum_required(VERSION 3.12)

project(Hello)

find_package(Clang REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(Hello SHARED Hello.cpp)

set_target_properties(Hello PROPERTIES
    LINKER_LANGUAGE CXX COMPILE_FLAGS "-fno-rtti")