cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE main.cpp Stock.cpp Menu.h)
set(HEADER Stock.h Menu.h)
add_executable(main ${SOURCE} ${HEADER})
