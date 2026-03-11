cmake_minimum_required(VERSION 3.20)

project(设计模式)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC src/2_声明和初始化/01_不要定义C风格的可变参函数.cpp) # 设置变量

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# C++14 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g -O2")

add_executable(main ${SRC})

