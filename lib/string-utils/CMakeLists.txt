cmake_minimum_required(VERSION 3.6)
project(string-utils-project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

set(SOURCE_FILES src/StringUtils.cpp include/StringUtils.h)
add_library(string-utils SHARED ${SOURCE_FILES})