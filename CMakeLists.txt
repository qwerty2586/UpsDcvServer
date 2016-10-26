cmake_minimum_required(VERSION 3.6)
project(UpsDcvServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp server.h server.cpp)
add_executable(UpsDcvServer ${SOURCE_FILES})