cmake_minimum_required(VERSION 3.26)

project(Eternal VERSION 0.1.0)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(ETERNAL_ENABLE_APPLICATIONS "Build applications" ON)
option(ETERNAL_ENABLE_TESTING "Build tests" ON)

list(PREPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_INSTALL_LIBDIR Lib)
set(CMAKE_INSTALL_BINDIR Bin)
set(CMAKE_INSTALL_INCLUDEDIR Include)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()

add_subdirectory(Source)

if(ETERNAL_ENABLE_APPLICATIONS)
    add_subdirectory(Applications)
endif()

if(ETERNAL_ENABLE_TESTING)
    include(CTest)
    add_subdirectory(Tests)
endif()

include(EternalPackage)
eternal_package()
