if(NOT TARGET slimenano::public)
    find_package(slimenano-public REQUIRED)
endif ()

target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC slimenano::public)