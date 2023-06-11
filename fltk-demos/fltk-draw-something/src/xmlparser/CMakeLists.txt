set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

aux_source_directory(. XML_PARSER_SRCS)

add_library(${lib_xmlparser} SHARED ${XML_PARSER_SRCS})

target_include_directories(${lib_xmlparser} PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(${lib_xmlparser} PROPERTIES VERSION 1.0 SOVERSION 1)
