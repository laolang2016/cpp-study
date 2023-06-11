set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${FLTK_LIBRARIES} ${lib_xmlparser})

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/copy_fltk_lib.py "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" "'${FLTK_LIBRARIES}'" "${PROJECT_NAME}"
# )

add_custom_target(copy_fltk_lib ALL
    DEPENDS
        ${PROJECT_NAME}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/copy_fltk_lib.py "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" "'${FLTK_LIBRARIES}'" "${PROJECT_NAME}"
)
