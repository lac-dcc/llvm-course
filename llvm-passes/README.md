# LLVM Passes

## Build
First, let us define a set of path variables:

```bash
$> LLVM_INSTALL_DIR=</path/to/llvm/>
$> LLVM_OPT=</path/to/opt>
```

For instance, if you built LLVM from source the commands above
will be like:

```bash
$> LLVM_INSTALL_DIR=/path/to/llvm-project/build
$> LLVM_OPT=$LLVM_INSTALL_DIR/bin/opt
```

Then, run CMake to prepare the build files. We will use the
folder `build` for that. You can use any build tool that you
want, e.g. ninja or make. In this example, we are using Ninja.

```bash
$> cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR -G "Ninja" -B build/ .
```

Next, move to the build folder and build the project:

```bash
$> cd build
$> cmake --build .
```

## Run
After building the project, the shared library will be at
`build/lib`. There is an example of a code written in LLVM IR at
`examples/foo.ll`. Let us first run the analysis printer on it:

```bash
$> $LLVM_OPT -load-pass-plugin build/lib/libAddConst.so \
$>  -passes="print<add-const>" -disable-output examples/foo.ll
```

You can run the transformation pass using opt:

```bash
$> $LLVM_OPT -load-pass-plugin build/lib/libAddConst.so \
$>  -passes="add-const" -S examples/foo.ll
```

Or using the llvm-based tool:

```bash
$> build/bin/addconst examples/foo.ll -o bar.ll
$> cat bar.ll
```
