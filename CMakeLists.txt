cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE ./project/src/main.cpp 
           ./project/src/Stock.cpp 
           ./project/src/Menu.cpp 
           ./project/src/indicator.cpp)
set(HEADER ./project/include/Stock.h 
           ./project/include/Menu.h 
           ./project/include/indicator.h)
add_executable(main ${SOURCE} ${HEADER})
