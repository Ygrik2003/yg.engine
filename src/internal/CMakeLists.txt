cmake_minimum_required(VERSION 3.28)

add_subdirectory(render)
add_subdirectory(window)

set(engine_sources ${render_sources} ${window_manager_sources})

add_library(yg_engine OBJECT ${engine_sources})
target_include_directories(yg_engine PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(
    yg_engine
    PRIVATE SDL3::SDL3
            libs::glad
            glm::glm
            Catch2::Catch2
            libassert::assert
    PUBLIC imgui::imgui)
set_target_properties(yg_engine PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(yg::engine ALIAS yg_engine)

add_executable(yg_engine_runner ${CMAKE_CURRENT_LIST_DIR}/main.cxx)
target_compile_definitions(yg_engine_runner PUBLIC YG_ENGINE_MAIN)
target_link_libraries(yg_engine_runner PRIVATE yg::engine)
