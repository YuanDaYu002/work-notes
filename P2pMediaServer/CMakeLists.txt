cmake_minimum_required(VERSION 3.6)
project(git_P2PMediaServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(git_P2PMediaServer ${SOURCE_FILES})