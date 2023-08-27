function( build_example SAMPLE_NAME SOURCES )

    add_executable( ${SAMPLE_NAME} ${SOURCES} )
    
    if ( LEAFY_SYSTEM_WINDOWS )
        if( CMAKE_COMPILER_IS_GNUCXX )
            execute_process( COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION )
            string( REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}" )
        endif()
        
        target_compile_definitions( ${TARGET} PRIVATE WIN32 )

        if( CMAKE_COMPILER_IS_GNUCXX )
            if( LEAFY_BUILD_SHARED_LIBS )
                set_target_properties( ${TARGET} PROPERTIES PREFIX "build/" )
            endif()

            set_target_properties( ${TARGET} PROPERTIES IMPORT_SUFFIX ".a" )
        endif()
    endif()

    target_link_libraries( ${SAMPLE_NAME} PRIVATE leafy::leafy )

    install(
        TARGETS ${SAMPLE_NAME}
        RUNTIME DESTINATION "${SHARE_PATH}/examples" COMPONENT examples
    )

    install(
        FILES ${SOURCES}
        DESTINATION "${SHARE_PATH}/examples" COMPONENT examples
    )
endfunction()

