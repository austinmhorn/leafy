cmake_minimum_required( VERSION 3.2 )

function( build_example SAMPLE_NAME SOURCES )

    add_executable( ${SAMPLE_NAME} ${SOURCES} )

    if( WIN32 )
        if( COMPILER_GCC_TDM )
            target_compile_options( ${SAMPLE_NAME} PUBLIC -shared-libgcc -shared-libstdc++ )
        endif()

        target_compile_definitions( ${SAMPLE_NAME} PRIVATE WIN32 )
    endif()

    target_include_directories( ${SAMPLE_NAME} PUBLIC $<BUILD_INTERFACE:${INCLUDE_PATH}> $<INSTALL_INTERFACE:include/> )

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

build_example( "HelloWorld" "HelloWorld.cpp" )

# Copy data directory to build cache directory to be able to run examples from
# there. Useful for testing stuff.
# Don't try to copy if the directories are the same.
if( NOT ( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" ) )
	add_custom_command(
		TARGET "HelloWorld"
		COMMAND "${CMAKE_COMMAND}"
		ARGS -E copy_directory "${PROJECT_SOURCE_DIR}/examples/data" "${PROJECT_BINARY_DIR}/examples/data"
	)
endif()

install(
	DIRECTORY data
	DESTINATION "${SHARE_PATH}/examples"
)
