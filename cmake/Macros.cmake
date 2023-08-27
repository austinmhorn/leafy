function( build_example SAMPLE_NAME SOURCES )

    add_executable( ${SAMPLE_NAME} ${SOURCES} )
    
    if ( LEAFY_SYSTEM_WINDOWS )
        if( CMAKE_COMPILER_IS_GNUCXX )
            execute_process( COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION )
            string( REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}" )
        endif()
        
        target_compile_definitions( ${SAMPLE_NAME} PRIVATE WIN32 )
        target_link_libraries( ${SAMPLE_NAME} PRIVATE "${LIBRARY_OUTPUT_PATH}/${CONFIG}/${TARGET}.dll" )

        if( CMAKE_COMPILER_IS_GNUCXX )
            if( LEAFY_BUILD_SHARED_LIBS )
                set_target_properties( ${SAMPLE_NAME} PROPERTIES PREFIX "" )
            endif()

            set_target_properties( ${SAMPLE_NAME} PROPERTIES IMPORT_SUFFIX ".a" )
        endif()
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

