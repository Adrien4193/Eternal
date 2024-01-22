function(eternal_export NAME)
    get_target_property(TARGET_TYPE ${NAME} TYPE)

    if(NOT TARGET_TYPE STREQUAL SHARED_LIBRARY)
        target_compile_definitions(${NAME} PUBLIC "ETERNAL_EXPORT=")
        return()
    endif()

    if(MSVC)
        target_compile_definitions(
            ${NAME}
            INTERFACE "ETERNAL_EXPORT=__declspec(dllimport)"
            PRIVATE "ETERNAL_EXPORT=__declspec(dllexport)"
        )
        return()
    endif()

    target_compile_definitions(
        ${NAME}
        PUBLIC "ETERNAL_EXPORT=__attribute__((visibility(\"default\")))"
    )
endfunction()
