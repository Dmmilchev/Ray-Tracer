cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
