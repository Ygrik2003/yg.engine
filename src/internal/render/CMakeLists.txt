cmake_minimum_required(VERSION 3.28)

file(
    GLOB_RECURSE
    render_sources
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/*.cxx
    ${CMAKE_CURRENT_LIST_DIR}/*.hxx)

set(render_sources ${render_sources} PARENT_SCOPE)
