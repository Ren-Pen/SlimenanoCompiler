

function(slimenano_test_target NAMESPACE TEST_NAME)

    set(TARGET_NAME test-${NAMESPACE}-${TEST_NAME})

    add_executable(${TARGET_NAME} ${ARGN})

endfunction()

function(slimenano_test_dependencies NAMESPACE TEST_NAME)

    set(TARGET_NAME test-${NAMESPACE}-${TEST_NAME})

    foreach (lib IN LISTS ARGN)

        if(NOT TARGET ${lib})
            find_package(${lib} REQUIRED)
        endif ()

        target_link_libraries(${TARGET_NAME} PRIVATE ${lib})

    endforeach ()

endfunction()