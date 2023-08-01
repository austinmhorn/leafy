cmake_minimum_required( VERSION 3.2 )

function( build_example SAMPLE_NAME SOURCES )

    add_executable( ${SAMPLE_NAME} ${SOURCES} )

    # For Visual Studio on Windows, export debug symbols (PDB files) to lib directory
        if(SFML_GENERATE_PDB)
            # PDB files are only generated in Debug and RelWithDebInfo configurations, find out which one
            if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
                set(SFML_PDB_POSTFIX "-d")
            else()
                set(SFML_PDB_POSTFIX "")
            endif()
    
            if(BUILD_SHARED_LIBS AND NOT THIS_STATIC)
                # DLLs export debug symbols in the linker PDB (the compiler PDB is an intermediate file)
                set_target_properties(${SAMPLE_NAME} PROPERTIES
                                      PDB_NAME "${target}${SFML_PDB_POSTFIX}"
                                      PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
            else()
                if(SFML_ENABLE_PCH)
                    message(VERBOSE "overriding PDB name for '${target}' with \"sfml-s${SFML_PDB_POSTFIX}\" due to PCH being enabled")
    
                    # For PCH builds with PCH reuse, the PDB name must be the same as the target that's being reused
                    set_target_properties(${SAMPLE_NAME} PROPERTIES
                                          COMPILE_PDB_NAME "sfml-system"
                                          COMPILE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
                else()
                    # Static libraries have no linker PDBs, thus the compiler PDBs are relevant
                    set_target_properties(${target} PROPERTIES
                                          COMPILE_PDB_NAME "${target}-s${SFML_PDB_POSTFIX}"
                                          COMPILE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
                endif()
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
