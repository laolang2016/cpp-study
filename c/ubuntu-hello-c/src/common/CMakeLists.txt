include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(. COMMON_SRCS)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(${lib_common} SHARED ${COMMON_SRCS})

target_link_libraries(${lib_common} zlog)

set_target_properties(${lib_common} PROPERTIES VERSION 1.0 SOVERSION 1)
