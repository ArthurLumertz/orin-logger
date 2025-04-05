cmake_minimum_required(VERSION 3.30)
project(Orin_Logger)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(Orin_Logger main.cpp)