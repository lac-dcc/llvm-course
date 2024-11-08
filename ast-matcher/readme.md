# AST Matcher

## How to setup LLVM

    cmake -DLLVM_ENABLE_PROJECTS="clang;clang-tools;compiler-rt" \
      -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD="X86" \
      -DBUILD_SHARED_LIBS=On -DLLVM_USE_LINKER=gold -G "Ninja" ../llvm

## How to setup tool

First at all, you need config where LLVM is building. After you can run the command below:

    ./setup

## How to execute examples

You can use the script run.sh. Below an example to use it:

    ./run input/ex1.cpp

## Reference

All material here is based on this [link](https://clang.llvm.org/docs/LibASTMatchersReference.html).