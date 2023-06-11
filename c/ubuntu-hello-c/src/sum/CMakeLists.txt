include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(. SUM_SRCS)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(${lib_sum} SHARED ${SUM_SRCS})

target_link_libraries(${lib_sum} zlog ${lib_common})

set_target_properties(${lib_sum} PROPERTIES VERSION 1.0 SOVERSION 1)
