cmake_minimum_required(VERSION 3.6)
project(P2pServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(P2pServer ${SOURCE_FILES})