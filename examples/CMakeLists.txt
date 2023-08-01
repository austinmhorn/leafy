cmake_minimum_required( VERSION 3.2 )

function( build_example SAMPLE_NAME SOURCES )

    add_executable( ${SAMPLE_NAME} ${SOURCES} )

    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${SAMPLE_NAME} PROPERTIES FOLDER "examples")

    # set the Visual Studio startup path for debugging
    set_target_properties(${SAMPLE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

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
