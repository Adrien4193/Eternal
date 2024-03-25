include(EternalLibrary)

eternal_library(Core ./Core)

if(WIN32)
    eternal_library(Platform ./Platform/Win32)
endif()

target_link_libraries(Platform PUBLIC Eternal::Core)

install(
    EXPORT EternalTargets
    FILE EternalTargets.cmake
    DESTINATION CMake
    NAMESPACE Eternal::
)

export(
    EXPORT EternalTargets
    FILE EternalTargets.cmake
    NAMESPACE Eternal::
)
