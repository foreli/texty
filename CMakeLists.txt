cmake_minimum_required(VERSION 3.8)
project(texty)

find_package (Threads)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-g -Wall -lpthread")
include_directories(${CMAKE_SOURCE_DIR}/include;${CMAKE_SOURCE_DIR}/socket/include)
link_directories(${CMAKE_SOURCE_DIR}/socket)
set(CLIENT_SOURCE_FILES
        source/client-main.cpp
        socket/include/msocket_client.hpp
        socket/include/message.hpp
        source/messenger-client.cpp
        include/messenger-client.hpp
        include/helpers.hpp
        include/formatter.hpp)

set(HOST_SOURCE_FILES
        source/host-main.cpp
        socket/include/msocket_client.hpp
        socket/include/msocket_host.hpp
        socket/include/message.hpp
        source/messenger-host.cpp
        include/messenger-host.hpp
        include/helpers.hpp
        include/formatter.hpp)

add_executable("texty-client" ${CLIENT_SOURCE_FILES})
add_executable("texty-host" ${HOST_SOURCE_FILES})
target_link_libraries(texty-client ${CMAKE_SOURCE_DIR}/socket/lib/socket.a)
target_link_libraries(texty-host ${CMAKE_SOURCE_DIR}/socket/lib/socket.a)
