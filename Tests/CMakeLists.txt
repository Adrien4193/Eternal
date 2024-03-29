add_library(Test STATIC Test.h Test.cpp)

set_target_properties(
    Test
    PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
)

target_include_directories(Test PUBLIC ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE ETERNAL_TESTS Unit/Test*.cpp)

foreach(TEST_SOURCE ${ETERNAL_TESTS})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WLE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
    target_link_libraries(${TEST_NAME} PRIVATE Eternal::Core Test)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
