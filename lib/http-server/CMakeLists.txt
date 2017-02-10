cmake_minimum_required(VERSION 3.6)
project(http-server-project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system thread regex coroutine)

include_directories(include)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ../http-parser/include)
    set(SOURCE_FILES src/Server.cpp src/Connection.cpp include/Connection.h include/Server.h include/IMiddleware.h)
    add_library(http-server SHARED ${SOURCE_FILES})
    target_link_libraries(http-server ${Boost_LIBRARIES} http-parser)
endif()