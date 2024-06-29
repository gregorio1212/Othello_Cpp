cmake_minimum_required(VERSION 3.29.3)
project(Othello)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)
add_executable(Othello ${SOURCES})
