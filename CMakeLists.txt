cmake_minimum_required(VERSION 2.6)
project(rabbit_server)

include_directories(src)
include_directories(src/base)
include_directories(src/utils)
include_directories(src/rpc)

add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(toy)

