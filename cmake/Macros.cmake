function( build_example SAMPLE_NAME SOURCES )

    add_executable( ${SAMPLE_NAME} ${SOURCES} )
    
    if ( LEAFY_SYSTEM_WINDOWS )
        target_compile_definitions( ${SAMPLE_NAME} PRIVATE WIN32 )
        target_link_libraries( ${SAMPLE_NAME} PRIVATE "${LIBRARY_OUTPUT_PATH}/${TARGET}.dll" )
    else()
        target_link_libraries( ${SAMPLE_NAME} PRIVATE leafy::leafy )
    endif()

    install(
        TARGETS ${SAMPLE_NAME}
        RUNTIME DESTINATION "${SHARE_PATH}/examples" COMPONENT examples
    )

    install(
        FILES ${SOURCES}
        DESTINATION "${SHARE_PATH}/examples" COMPONENT examples
    )
endfunction()


