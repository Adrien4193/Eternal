add_library(Eternal)

if(MSVC)
    target_compile_options(Eternal PRIVATE /W4 /WX)
endif()

set_target_properties(Eternal PROPERTIES CXX_STANDARD 20)
set_target_properties(Eternal PROPERTIES CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ETERNAL_PUBLIC_HEADERS Public/*.h)
file(GLOB_RECURSE ETERNAL_PRIVATE_SOURCES Public/*.cpp Private/*.h Private/*.cpp)

if(WIN32)
    set(ETERNAL_PLATFORM Win32)
else()
    message(FATAL_ERROR "Platform not supported")
endif()

file(GLOB_RECURSE ETERNAL_PLATFORM_SOURCES Platform/${ETERNAL_PLATFORM}/*.h Platform/${ETERNAL_PLATFORM}/*.cpp)

target_sources(Eternal
    PRIVATE ${ETERNAL_PRIVATE_SOURCES} ${ETERNAL_PLATFORM_SOURCES}
    PUBLIC FILE_SET HEADERS
    BASE_DIRS Public
    FILES ${ETERNAL_PUBLIC_HEADERS}
)

target_include_directories(Eternal
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        Private
        Platform/${ETERNAL_PLATFORM}
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
