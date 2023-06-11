cmake_minimum_required(VERSION 3.25)

# 指定 c++ 版本为 14
set(CMAKE_CXX_STANDARD 14)
# 如果编译器不支持指定的版本, 则终止构建而不是下调版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 仅使用标准c++的编译器选项
set(CMAKE_CXX_EXTENSIONS OFF)

project(cpp-hello CXX)

add_executable(${PROJECT_NAME} main.cpp)
