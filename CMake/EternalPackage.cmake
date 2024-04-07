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

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/CMake/EternalConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/EternalConfig.cmake
    INSTALL_DESTINATION CMake
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/EternalConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/EternalConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/EternalConfigVersion.cmake
    DESTINATION CMake
)
