cmake_minimum_required(VERSION 3.15.0)
include(SlimenanoLibraryInstall)

set(NAMESPACE "slimenano")
set(LIB_NAME "utils")
set(LIB_VERSION "1.0.0")
set(LIBRARY_TARGET_NAME "${NAMESPACE}-${LIB_NAME}")

project(${NAMESPACE}${LIB_NAME}
        VERSION ${LIB_VERSION}
        DESCRIPTION "This is a Slimenano free ${LIB_NAME} library"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(SRC_FILES "${SRC_DIR}/lib_main.cpp"
)

set(INCLUDE_FILES "${SRC_DIR}/slimenano/avl_tree.hpp"
)

add_library(${LIBRARY_TARGET_NAME} ${SRC_FILES} ${INCLUDE_FILES})
add_library(${NAMESPACE}::${LIB_NAME} ALIAS ${LIBRARY_TARGET_NAME})

target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${SRC_DIR}>)
target_compile_definitions(${LIBRARY_TARGET_NAME} PRIVATE "SLIMENANO_LIBRARY_")

if(MSVC)
    target_compile_options(${LIBRARY_TARGET_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${LIBRARY_TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(cmake/dependencies.cmake)
slimenano_install("${LIBRARY_TARGET_NAME}" ${LIB_VERSION} "${NAMESPACE}" "${LIB_NAME}" "${SRC_DIR}")

include(SlimenanoTest)

set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")

slimenano_test_target("slimenano"
        "utils-avl_tree"
        "${TEST_DIR}/avl_tree/test_avl_tree.cpp"
)

slimenano_test_dependencies("slimenano"
        "utils-avl_tree"
        "slimenano::utils"
)