cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE main.cpp candle.cpp indicator.h)
set(HEADER candle.h indicator.h)
add_executable(main ${SOURCE} ${HEADER})
