add_library(Test STATIC Test.h Test.cpp)

set_target_properties(
    Test
    PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
)

target_include_directories(Test PUBLIC ${CMAKE_CURRENT_LIST_DIR})
