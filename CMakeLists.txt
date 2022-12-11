cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE main.cpp Stock.cpp Menu.cpp indicator.cpp)
set(HEADER Stock.h Menu.h indicator.h)
add_executable(main ${SOURCE} ${HEADER})
