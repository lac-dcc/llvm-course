# LLVM Signature Recover Pass

## Description
This is an LLVM pass that reconstructs signature of functions using LLVM debug information. 

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
`examples/Linked_List.c`. To compile and run the pass on it
follow the commands below:

```bash
$ cd example
$ $LLVM_BIN/clang -g -emit-llvm Linked_List.c -o Linked_List.bc
$ $LLVM_BIN/opt -load ../build/lib/libSignatureRecovert.so -recsign -disable-output Linked_List.bc
```
If you want to visualize the IR, run llvm disassembler:
```bash
$ $LLVM_BIN/llvm-dis Linked_List.bc
```
The file *Linked_List.ll* contains human-readable IR.


