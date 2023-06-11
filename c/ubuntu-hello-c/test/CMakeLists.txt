cmake_minimum_required(VERSION 3.25)

project(hello_c_test C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH True)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(. TEST_SRCS)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} ${TEST_SRCS})
target_link_libraries(${PROJECT_NAME} cunit zlog ${lib_common} ${lib_sum})
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")

add_custom_target(coverage
    DEPENDS
        ${PROJECT_NAME}
    COMMAND lcov -d ${CMAKE_SOURCE_DIR} -t 'hello-c 测试覆盖率报告' -o ${CMAKE_BINARY_DIR}/coverage/app.info -b ${CMAKE_SOURCE_DIR} -c
    COMMAND lcov ${CMAKE_BINARY_DIR}/coverage/app.info -o ${CMAKE_BINARY_DIR}/html
)

