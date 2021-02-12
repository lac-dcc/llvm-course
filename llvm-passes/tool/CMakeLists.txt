add_executable(addconst
    Main.cpp
    ../lib/AddConstAnalysis.cpp
    ../lib/AddConstPass.cpp
    )

target_link_libraries(addconst LLVMPasses)
target_include_directories(addconst PRIVATE "../include")
