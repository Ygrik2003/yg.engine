cmake_minimum_required(VERSION 3.28)

# For Windows download VulkanSDK (https://www.lunarg.com/vulkan-sdk/)
# and use env variable VULKAN_SDK=C:/VulkanSDK/1.3.280.0
find_package(Vulkan REQUIRED)

# Catch2::Catch2 Catch2::Catch2WithMain
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Catch2)
# SDL3::SDL3
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SDL)
# glm::glm
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glm)
# Tracy::TracyClient
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tracy)
# spdlog
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/spdlog)
# libassert::assert
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libassert)

#imgui
set(imgui_src
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imconfig.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_rectpack.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_textedit.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imstb_truetype.h)

set(imgui_backand_src
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_sdl3.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_sdl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl2.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_vulkan.h
    ${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_vulkan.cpp)

add_library(imgui STATIC ${imgui_src} ${imgui_backand_src})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/imgui)
target_link_libraries(imgui PRIVATE SDL3::SDL3 Vulkan::Vulkan libs::glad)
set_target_properties(imgui PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_library(imgui::imgui ALIAS imgui)
