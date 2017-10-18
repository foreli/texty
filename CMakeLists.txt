cmake_minimum_required(VERSION 3.8)
project(texty)

find_package (Threads)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-g -Wall -I../socket/include -I../include")

set(SOURCE_FILES
        source/main.cpp
        socket/include/msocket_client.hpp
        socket/include/msocket_host.hpp)
add_executable(texty ${SOURCE_FILES})
target_link_libraries(texty ${CMAKE_SOURCE_DIR}/socket/socket.a)
target_link_libraries (texty ${CMAKE_THREAD_LIBS_INIT})