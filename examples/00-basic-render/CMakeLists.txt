cmake_minimum_required(VERSION 3.28)

add_executable(00_basic_render_triangle triangle.cxx)
target_link_libraries(00_basic_render_triangle PRIVATE yg::engine)

add_custom_command(
    TARGET 00_basic_render_triangle
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/data
        $<TARGET_FILE_DIR:00_basic_render_triangle>/data)
