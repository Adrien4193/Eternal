function(eternal_library TARGET HEADERS SOURCES)
    add_library(${TARGET})
    add_library(Eternal::${TARGET} ALIAS ${TARGET})

    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME Eternal${TARGET})

    target_sources(
        ${TARGET}
        PUBLIC
        FILE_SET HEADERS
        FILES ${HEADERS}
        PRIVATE
        ${SOURCES}
    )

    target_include_directories(
        ${TARGET}
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    include(EternalExport)
    eternal_export(${TARGET})

    install(
        TARGETS ${TARGET}
        EXPORT EternalTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT ${TARGET}
    )
endfunction()
