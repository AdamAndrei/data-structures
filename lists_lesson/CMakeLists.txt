cmake_minimum_required(VERSION 3.16)
project(lists_lesson CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_BINARY_DIR}/.*")

add_executable(lists_lesson ${SOURCES})
target_include_directories(lists_lesson PRIVATE ${CMAKE_SOURCE_DIR}/include)
