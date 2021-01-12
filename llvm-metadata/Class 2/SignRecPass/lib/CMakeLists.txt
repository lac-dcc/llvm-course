
#===============================================================================
# See: https://llvm.org/docs/CMake.html#developing-llvm-passes-out-of-source
#===============================================================================
add_library(SignatureRecover MODULE
    SignatureRecover.cpp)

#target_include_directories(AddConst PRIVATE
#    "${CMAKE_CURRENT_SOURCE_DIR}/../include")
