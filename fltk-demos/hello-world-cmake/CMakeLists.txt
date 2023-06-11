cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH True)

set(lib_xmlparser xmlparser)

project(fltk-hello CXX)

find_package (Python3 COMPONENTS Interpreter Development REQUIRED)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

add_subdirectory(src)

