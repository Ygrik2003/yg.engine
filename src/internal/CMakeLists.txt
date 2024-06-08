cmake_minimum_required(VERSION 3.28)

add_subdirectory(render)
add_subdirectory(window)
add_subdirectory(tools)

set(engine_sources ${render_sources} ${window_manager_sources} ${tools_sources})
# list(FILTER engine_sources EXCLUDE "\.unittest\.cxx")

add_library(yg_engine OBJECT ${engine_sources})
target_include_directories(yg_engine PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(
    yg_engine
    PRIVATE
        SDL3::SDL3
        libs::glad
        glm::glm
        imgui::imgui # Need custom UI class for creating UI without direct invoke imgui
    PUBLIC Catch2::Catch2 libassert::assert spdlog)
set_target_properties(yg_engine PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(yg::engine ALIAS yg_engine)

add_executable(yg_engine_runner ${CMAKE_CURRENT_LIST_DIR}/main.cxx)
target_compile_definitions(yg_engine_runner PRIVATE YG_ENGINE_MAIN)
target_link_libraries(yg_engine_runner PRIVATE yg::engine)

add_executable(yg_engine_unit_tests ${CMAKE_CURRENT_LIST_DIR}/main.cxx)
target_compile_definitions(yg_engine_unit_tests PRIVATE YG_ENGINE_MAIN
                                                        __YG_UNIT_TESTS__)
target_link_libraries(yg_engine_unit_tests PRIVATE yg::engine)
