include(EternalLibrary)

eternal_library(Core)

if(WIN32)
    eternal_library(Windows)
    target_link_libraries(Windows PUBLIC Eternal::Core)
endif()

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
