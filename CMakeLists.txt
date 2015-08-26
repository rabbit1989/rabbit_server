cmake_minimum_required(VERSION 2.6)
project(rabbit_server)

include_directories(src/base)
include_directories(src/utils)

add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(toy)

