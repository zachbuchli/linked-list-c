cmake_minimum_required(VERSION 3.0.0)
project(stringlist VERSION 0.1.0)

include(CTest)
enable_testing()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

add_executable(stringlist main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
