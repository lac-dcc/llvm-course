#!/usr/bin/env bash
# =========================================================================== #
LLVM_BUILD_DIR="...path_to/llvm-project/build"

mkdir -p build
BUILD_DIR=$(realpath -L ./build)

cc=$LLVM_BUILD_DIR/bin/clang
cxx=$LLVM_BUILD_DIR/bin/clang++

cmake -S . -B $BUILD_DIR -G "Ninja"              \
    -DLLVM_DIR=${LLVM_BUILD_DIR}/lib/cmake/llvm   \
    -DClang_DIR=${LLVM_BUILD_DIR}/lib/cmake/clang \
    -DLLVM_INSTALL_DIR=$LLVM_BUILD_DIR \
    -DCMAKE_C_COMPILER=$cc                      \
    -DCMAKE_CXX_COMPILER=$cxx                   \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .

NPROC=$(nproc)
ninja -j $NPROC -C $BUILD_DIR
# =========================================================================== #
