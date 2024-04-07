add_library(Test STATIC Test.h Test.cpp)

set_target_properties(
    Test
    PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
)

target_include_directories(Test PUBLIC ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SOURCES Unit/Test*.cpp)

foreach(SOURCE ${SOURCES})
    get_filename_component(NAME ${SOURCE} NAME_WLE)
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
    target_link_libraries(${NAME} PRIVATE Eternal::Core Test)
    add_test(NAME ${NAME} COMMAND ${NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
