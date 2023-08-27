cmake_minimum_required( VERSION 3.2 )



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
if( LEAFY_SYSTEM_WINDOWS ) 
    install(
        FILES ${PROJECT_BINARY_DIR}$<CONFIG>/${TARGET}.dll
        DESTINATION bin
    )
endif()
