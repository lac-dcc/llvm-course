
find_package(Clang REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(forMatcher forMatcher.cpp)

target_link_libraries(forMatcher clangTooling)