function(eternal_library NAME FOLDER)
    add_library(${NAME})

    add_library(Eternal::${NAME} ALIAS ${NAME})

    file(GLOB_RECURSE PUBLIC_HEADERS ${FOLDER}/Public/*.h)

    file(
        GLOB_RECURSE
        PRIVATE_SOURCES
        ${FOLDER}/Public/*.cpp
        ${FOLDER}/Private/*.h
        ${FOLDER}/Private/*.cpp
    )

    target_sources(
        ${NAME}
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${FOLDER}/Public
        FILES ${PUBLIC_HEADERS}
        PRIVATE
        ${PRIVATE_SOURCES}
    )

    target_include_directories(
        ${NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/Public>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE ${FOLDER}/Private
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
