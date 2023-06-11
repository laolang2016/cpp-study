include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(. SRCS)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} zlog ${lib_common} ${lib_sum} ${lib_human})

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")
