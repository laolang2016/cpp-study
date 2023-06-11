cmake_minimum_required(VERSION 3.25)

project(hello_c C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH True)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")



set(lib_common common)
set(lib_sum sum)
set(lib_human human)

configure_file(${CMAKE_SOURCE_DIR}/zlog.conf ${CMAKE_BINARY_DIR}/bin/zlog.conf COPYONLY)

add_subdirectory(src)

add_subdirectory(test)
enable_testing()
add_test(NAME hello_c_test COMMAND hello_c_test)
