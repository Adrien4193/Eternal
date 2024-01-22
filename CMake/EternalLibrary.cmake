function(eternal_library NAME)
    add_library(${NAME})

    add_library(Eternal::${NAME} ALIAS ${NAME})

    file(GLOB_RECURSE PUBLIC_HEADERS ${NAME}/Public/*.h)

    file(
        GLOB_RECURSE
        PRIVATE_SOURCES
        ${NAME}/Public/*.cpp
        ${NAME}/Private/*.h
        ${NAME}/Private/*.cpp
    )

    target_sources(
        ${NAME}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${NAME}/Public
        FILES ${PUBLIC_HEADERS}
        PRIVATE
        ${PRIVATE_SOURCES}
    )

    target_include_directories(
        ${NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/Public>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE ${NAME}/Private
    )

    include(EternalExport)
    eternal_export(${NAME})

    install(
        TARGETS ${NAME}
        EXPORT EternalTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endfunction()
