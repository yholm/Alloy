cmake_minimum_required(VERSION 3.30.0)
project(alloy VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp")

add_executable(alloy ${SOURCES})

target_include_directories(alloy PRIVATE "${CMAKE_SOURCE_DIR}/include")
