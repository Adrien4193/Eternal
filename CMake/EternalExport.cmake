function(eternal_export TARGET)
    string(TOUPPER ${TARGET} TARGET_UPPERCASE)

    set(MACRO_NAME ETERNAL_${TARGET_UPPERCASE}_API)

    get_target_property(TARGET_TYPE ${TARGET} TYPE)

    if(NOT TARGET_TYPE STREQUAL SHARED_LIBRARY)
        target_compile_definitions(${TARGET} PUBLIC "${MACRO_NAME}=")
        return()
    endif()

    if(MSVC)
        target_compile_definitions(
            ${TARGET}
            INTERFACE "${MACRO_NAME}=__declspec(dllimport)"
            PRIVATE "${MACRO_NAME}=__declspec(dllexport)"
        )
        return()
    endif()

    target_compile_definitions(
        ${TARGET}
        PUBLIC "${MACRO_NAME}=__attribute__((visibility(\"default\")))"
    )
endfunction()
