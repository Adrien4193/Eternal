include(EternalLibrary)

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

eternal_library(Core "${HEADERS}" "${SOURCES}")
