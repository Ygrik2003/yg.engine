cmake_minimum_required(VERSION 3.28)

project(yg_engine VERSION 0.0.1 LANGUAGES C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(examples)
