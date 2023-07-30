add_library(Eternal)

if(MSVC)
    target_compile_options(Eternal PRIVATE /W4 /WX)
endif()

set_target_properties(Eternal PROPERTIES CXX_STANDARD 20)
set_target_properties(Eternal PROPERTIES CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ETERNAL_PUBLIC Public/*.h)
file(GLOB_RECURSE ETERNAL_PRIVATE Public/*.cpp)

target_sources(Eternal
    PRIVATE ${ETERNAL_PRIVATE}
    PUBLIC FILE_SET HEADERS
    BASE_DIRS Public
    FILES ${ETERNAL_PUBLIC}
)

target_include_directories(Eternal PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
    $<INSTALL_INTERFACE:Include>
)

install(TARGETS Eternal
    EXPORT EternalTargets
    RUNTIME DESTINATION Bin
    LIBRARY DESTINATION Lib
    ARCHIVE DESTINATION Lib
    FILE_SET HEADERS DESTINATION Include
)

install(EXPORT EternalTargets
    FILE EternalTargets.cmake
    DESTINATION CMake
)
