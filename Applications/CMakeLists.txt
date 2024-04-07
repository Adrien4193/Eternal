add_executable(Sandbox Sandbox.cpp)

target_link_libraries(Sandbox PRIVATE Eternal::Core Eternal::Platform)

install(
    TARGETS Sandbox
    EXPORT EternalTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
