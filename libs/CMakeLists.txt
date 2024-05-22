cmake_minimum_required(VERSION 3.28)

add_library(
    glad STATIC
    ${CMAKE_CURRENT_LIST_DIR}/glad/include/glad/glad.h
    ${CMAKE_CURRENT_LIST_DIR}/glad/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_LIST_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_LIST_DIR}/glad/include)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(libs::glad ALIAS glad)
