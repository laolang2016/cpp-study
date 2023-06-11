cmake_minimum_required(VERSION 3.0)

project(cpp-hello CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH True)

set(lib_calc calc)
set(lib_xmlparser xmlparser)

add_subdirectory(src)
