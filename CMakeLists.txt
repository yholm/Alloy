cmake_minimum_required(VERSION 3.30.0)
project(alloy VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_executable(alloy ${SOURCES})

target_include_directories(alloy PRIVATE "${CMAKE_SOURCE_DIR}/include")
