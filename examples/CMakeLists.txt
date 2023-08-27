cmake_minimum_required( VERSION 3.2 )

function( build_example SAMPLE_NAME SOURCES )

    add_executable( ${SAMPLE_NAME} ${SOURCES} )
    
    add_library(leafy STATIC IMPORTED GLOBAL)
    set_property(${SAMPLE_NAME} ${SOURCES} APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
    if (LEAFY_SYSTEM_WINDOWS)
        set_target_properties(${SOURCES} PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
            IMPORTED_LOCATION_DEBUG "${LIBRARY_OUTPUT_PATH}/leafy.lib")
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

