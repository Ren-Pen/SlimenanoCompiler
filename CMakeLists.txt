cmake_minimum_required(VERSION 3.15)
project(SlimenanoCompiler)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-utils")

add_subdirectory(deps)
add_subdirectory(modules)

