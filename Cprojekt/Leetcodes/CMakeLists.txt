cmake_minimum_required(VERSION 3.21)
project(Leetcodes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L /Library/Developer/CommandLineTools/usr/lib")
include_directories(/Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/include)

add_subdirectory(Solutions)
add_executable(Leetcodes main.cpp)
target_link_libraries(Leetcodes SolutionsLib)