cmake_minimum_required(VERSION 3.28)

add_executable(01_unitests ${CMAKE_CURRENT_LIST_DIR}/main.cxx)
target_link_libraries(01_unitests PRIVATE Catch2::Catch2WithMain)
