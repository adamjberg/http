cmake_minimum_required(VERSION 3.5)
project(http-parser-project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.61 REQUIRED COMPONENTS system thread regex coroutine)

include_directories(include)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(SOURCE_FILES src/HttpParser.cpp include/HttpParser.h include/HttpRequest.h include/HttpResponse.h include/HttpMethods.h)
    add_library(http-parser SHARED ${SOURCE_FILES})
    target_link_libraries(http-parser ${Boost_LIBRARIES})
endif()
