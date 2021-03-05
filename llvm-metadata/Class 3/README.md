# LLVM Variable Tracking Pass

## Description
This is an LLVM pass that track variable assignments in the IR LLVM debug information. 

## Requirements
LLVM + Clang version 10.0.0 or greater.

## Build
Define a set of path variables:

```bash
$ LLVM_INSTALL_DIR=</path/to/llvm/>
$ LLVM_BIN=</path/to/llvm/bin>
```

For instance, if you built LLVM from source the commands above
will be like:

```bash
$ LLVM_INSTALL_DIR=/path/to/llvm-project/build
$ LLVM_BIN=$LLVM_INSTALL_DIR/bin
```


Then, create the build directory and run CMake to prepare the build files. We will use the
folder `build` for that. You can use any build tool that you
want, e.g. ninja or make.

```bash
$ mkdir build
$ cd build
$ cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR ../
```

Next, build the project:

```bash
$ cmake --build .
```

## Run
After building the project, the shared library will be at
`build/lib`. There is an example of a code written in LLVM IR at
`examples/simple-integer.c`. To compile and run the pass on it
follow the commands below:

```bash
$ cd example
$ $LLVM_BIN/-c -Xclang -disable-O0-optnone -emit-llvm -g simple-integer.c -o simple-integer.bc
$ $LLVM_BIN/opt -mem2reg simple-integer.bc -o simple-integer.bc
$ $LLVM_BIN/opt -load ../build/lib/libVarTracking.so -vartrack -disable-output simple-integer.bc
```
If you want to visualize the IR, run llvm disassembler:
```bash
$ $LLVM_BIN/llvm-dis simple-integer.bc
```
The file *simple-integer.ll* contains human-readable IR.


