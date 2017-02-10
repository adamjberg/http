cmake_minimum_required(VERSION 3.6)
project(http)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)


add_subdirectory(lib/string-utils)
add_subdirectory(lib/http-parser)
add_subdirectory(lib/http-server)

include_directories(${Boost_INCLUDE_DIRS} lib/http-parser/include lib/http-server/include lib/string-utils/include lib/json)
set(SOURCE_FILES main.cpp lib/string-utils/include/StringUtils.h lib/string-utils/src/StringUtils.cpp pch.h)
add_executable(http ${SOURCE_FILES})
target_link_libraries(http ${Boost_LIBRARIES} http-server string-utils)

set_target_properties(http PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pch.h")
cotire(http)