function(eternal_export NAME)
    string(TOUPPER ${NAME} NAME_UPPERCASE)

    set(MACRO_NAME ETERNAL_${NAME_UPPERCASE}_API)

    get_target_property(TARGET_TYPE ${NAME} TYPE)

    if(NOT TARGET_TYPE STREQUAL SHARED_LIBRARY)
        target_compile_definitions(${NAME} PUBLIC "${MACRO_NAME}=")
        return()
    endif()

    if(MSVC)
        target_compile_definitions(
            ${NAME}
            INTERFACE "${MACRO_NAME}=__declspec(dllimport)"
            PRIVATE "${MACRO_NAME}=__declspec(dllexport)"
        )
        return()
    endif()

    target_compile_definitions(
        ${NAME}
        PUBLIC "${MACRO_NAME}=__attribute__((visibility(\"default\")))"
    )
endfunction()
