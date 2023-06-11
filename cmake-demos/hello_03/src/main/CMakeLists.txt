set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

aux_source_directory(. SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${lib_util} ${lib_calc} ${lib_xmlparser})

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")
