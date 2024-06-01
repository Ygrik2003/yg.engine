cmake_minimum_required(VERSION 3.28)

file(
    GLOB_RECURSE
    tools_sources
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/*.cxx
    ${CMAKE_CURRENT_LIST_DIR}/*.hxx)

set(tools_sources ${tools_sources} PARENT_SCOPE)
message(DEBUG "Tools sources: ${tools_sources}")
