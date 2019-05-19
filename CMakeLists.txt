cmake_minimum_required(VERSION 3.13)
project(Shrage)

set(CMAKE_CXX_STANDARD 14)

add_executable(Shrage main.cpp )
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})