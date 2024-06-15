include(EternalLibrary)

if(WIN32)
    set(PLATFORM "Win32")
endif()

file(GLOB_RECURSE HEADERS ${PLATFORM}/*.h)
file(GLOB_RECURSE SOURCES ${PLATFORM}/*.cpp)

list(APPEND HEADERS Platform.h)

eternal_library(Platform "${HEADERS}" "${SOURCES}")

target_link_libraries(Platform PUBLIC Core)

string(TOUPPER ${PLATFORM} PLATFORM_UPPERCASE)
target_compile_definitions(Platform PUBLIC "ETERNAL_PLATFORM_${PLATFORM_UPPERCASE}")
