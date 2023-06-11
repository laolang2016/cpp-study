include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(. HUMAN_SRCS)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(${lib_human} SHARED ${HUMAN_SRCS})

set_target_properties(${lib_human} PROPERTIES VERSION 1.0 SOVERSION 1)
