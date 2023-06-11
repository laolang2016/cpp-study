set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

aux_source_directory(. CALC_SRCS)

add_library(${lib_calc} SHARED ${CALC_SRCS})

target_include_directories(${lib_calc} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${lib_calc} ${lib_util})

set_target_properties(${lib_calc} PROPERTIES VERSION 1.0 SOVERSION 1)
