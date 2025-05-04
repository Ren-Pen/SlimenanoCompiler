cmake_minimum_required(VERSION 3.15.0)
include(SlimenanoLibraryInstall)

set(NAMESPACE "slimenano")
set(LIB_NAME "public")
set(LIB_VERSION "1.0.0")
set(LIBRARY_TARGET_NAME "${NAMESPACE}-${LIB_NAME}")

project(${NAMESPACE}${LIB_NAME}
        VERSION ${LIB_VERSION}
        DESCRIPTION "This is a Slimenano ${LIB_NAME} dependency"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/include")

set(INCLUDE_FILES "${SRC_DIR}/slimenano/slimenano_api.hpp"
)

add_library(${LIBRARY_TARGET_NAME} INTERFACE ${INCLUDE_FILES})
add_library(${NAMESPACE}::${LIB_NAME} ALIAS ${LIBRARY_TARGET_NAME})

target_include_directories(${LIBRARY_TARGET_NAME} INTERFACE $<BUILD_INTERFACE:${SRC_DIR}>)
slimenano_install("${LIBRARY_TARGET_NAME}" ${LIB_VERSION} "${NAMESPACE}" "${LIB_NAME}" "${SRC_DIR}")
