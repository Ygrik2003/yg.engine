cmake_minimum_required(VERSION 3.28)

file(
    GLOB_RECURSE
    window_manager_sources
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/*.cxx
    ${CMAKE_CURRENT_LIST_DIR}/*.hxx)

set(window_manager_sources ${window_manager_sources} PARENT_SCOPE)
