cmake_minimum_required(VERSION 3.0)
project(blue)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(blue src/main.cpp)
target_link_libraries(blue)
