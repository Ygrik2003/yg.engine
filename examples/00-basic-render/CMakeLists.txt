cmake_minimum_required(VERSION 3.28)

add_executable(00_basic_render_triangle triangle.cxx)
target_link_libraries(00_basic_render_triangle PRIVATE yg::engine)
