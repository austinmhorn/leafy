cmake_minimum_required(VERSION 3.21)

set( LEAFY_MAJOR_VERSION 0 )
set( LEAFY_MINOR_VERSION 1 )
set( LEAFY_REVISION_VERSION 0 )
set( LEAFY_VERSION ${LEAFY_MAJOR_VERSION}.${LEAFY_MINOR_VERSION}.${LEAFY_REVISION_VERSION} )

set( PROJECT_NAME "leafy" )
project( ${PROJECT_NAME} LANGUAGES CXX VERSION ${LEAFY_VERSION} )
set( TARGET ${PROJECT_NAME} )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Include the Config file
include( cmake/Config.cmake )
# Include the Macros file
include( cmake/Macros.cmake )

# User Defined Options
option( LEAFY_BUILD_SHARED_LIBS "Build shared library."            ON )
option( LEAFY_BUILD_EXAMPLES    "Build examples."                  ON )
option( LEAFY_BUILD_DOC         "Generate API documentation."      OFF)
option( LEAFY_INCLUDE_FONT      "Include default font in library." ON )
set( BUILD_SHARED_LIBS ${LEAFY_BUILD_SHARED_LIBS} )

# Find OpenGL
find_package( OpenGL REQUIRED )
# Find SFML
if( NOT TARGET sfml-graphics )
    find_package( SFML 2.5 REQUIRED COMPONENTS graphics window system network audio )
endif()

# Set source and include paths
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include/" )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src/" )

# Recursively find project files
file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.hpp" )
file( GLOB_RECURSE INLS "${INCLUDE_PATH}/*.inl" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp"  )

if( LEAFY_INCLUDE_FONT )
	list(APPEND CPPS "${SOURCE_PATH}/leafy/Engine/Sansation.cpp")
endif()

# Define the path of additional CMake modules
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/" )
# Set the library output directory
set( LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib" )

# Link sources to library
add_library( ${TARGET} ${CPPS} ${INLS} ${HPPS} )

# Include header file directory to target
target_include_directories( ${TARGET} PUBLIC $<BUILD_INTERFACE:${INCLUDE_PATH}> $<INSTALL_INTERFACE:include/> )

# Assign target properties
if( NOT LEAFY_BUILD_SHARED_LIBS )
    target_compile_definitions( ${TARGET} PUBLIC LEAFY_STATIC )
    set_target_properties( ${TARGET} PROPERTIES CMAKE_DEBUG_POSTFIX -s-d )
    set_target_properties( ${TARGET} PROPERTIES CMAKE_RELEASE_POSTFIX -s )
    set_target_properties( ${TARGET} PROPERTIES CMAKE_MINSIZEREL_POSTFIX -s )
else ()
    set_target_properties( ${TARGET} PROPERTIES CMAKE_DEBUG_POSTFIX -d )
endif ()

if( LEAFY_INCLUDE_FONT )
    target_compile_definitions( ${TARGET} PRIVATE LEAFY_INCLUDE_FONT )
endif()

# Tell the compiler to export when necessary.
set_target_properties( ${TARGET} PROPERTIES DEFINE_SYMBOL LEAFY_EXPORTS )

target_link_libraries( ${TARGET} PUBLIC sfml-graphics sfml-window sfml-system sfml-network sfml-audio ${OPENGL_gl_LIBRARY} )

# Platform- and compiler-specific options.
if( WIN32 )
    option( LEAFY_STATIC_STD_LIBS "Use statically linked standard/runtime libraries? This option must match the one used for SFML." OFF)

    # Determine whether we're dealing with a TDM compiler or not
    if( CMAKE_COMPILER_IS_GNUCXX )
        execute_process( COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION )
        string( REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}" )
    endif()

    # Allow the static linking of the runtime libraries
    if( LEAFY_STATIC_STD_LIBS )
        if( LEAFY_BUILD_SHARED_LIBS )
            message( FATAL_ERROR "\n-> LEAFY_STATIC_STD_LIBS and LEAFY_BUILD_SHARED_LIBS are not compatible.\n-> They lead to multiple runtime environments which results in undefined behavior.\n" )
        else()
            target_compile_definitions( ${TARGET} PUBLIC LEAFY_STATIC )

            if( MSVC )
                foreach(flag
                        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
                    if( ${flag} MATCHES "/MD" )
                    string( REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}" )
                    endif()
                endforeach()
            elseif( CMAKE_COMPILER_IS_GNUCXX AND NOT COMPILER_GCC_TDM )
                target_compile_options( ${TARGET} PUBLIC -static-libgcc -static-libstdc++ )
            endif()
        endif()
    elseif( COMPILER_GCC_TDM )
        target_compile_options( ${TARGET} PUBLIC -shared-libgcc -shared-libstdc++ )
    endif()

    target_compile_definitions( ${TARGET} PRIVATE WIN32 )

    if( CMAKE_COMPILER_IS_GNUCXX )
        if( LEAFY_BUILD_SHARED_LIBS )
            set_target_properties( ${TARGET} PROPERTIES PREFIX "" )
        endif()

        set_target_properties( ${TARGET} PROPERTIES IMPORT_SUFFIX ".a" )
    endif()

    set( SHARE_PATH "." )
    set( LIB_PATH "lib" )
elseif( APPLE )
    find_library( FOUNDATION_LIBRARY Foundation REQUIRED )
    find_library( COREGRAPHICS_LIBRARY CoreGraphics REQUIRE D)

    target_link_libraries( ${TARGET} PUBLIC ${FOUNDATION_LIBRARY} ${COREGRAPHICS_LIBRARY} )
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/leafy" )
    set( LIB_PATH "lib" )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
    find_package( X11 REQUIRED )
    target_link_libraries( ${TARGET} PUBLIC ${X11_LIBRARIES} )
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/leafy" )
    
    if( LIB_SUFFIX )
        set( LIB_PATH "lib${LIB_SUFFIX}" )
    else()
        set( LIB_PATH "lib" )
    endif()
else()
    set( SHARE_PATH "${CMAKE_INSTALL_PREFIX}/share/leafy" )
    set( LIB_PATH "lib" )
endif()

if( CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options( ${TARGET} PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic )
endif()

if( LEAFY_BUILD_EXAMPLES )
    add_subdirectory( "examples" )
endif()

if(LEAFY_BUILD_SHARED_LIBS)
    set(TARGET_CONFIG_TYPE "Shared")
else()
    set(TARGET_CONFIG_TYPE "Static")
endif()

set( TARGETS_CONFIG_FILENAME "${TARGET}${TARGET_CONFIG_TYPE}Targets" )

add_library( ${PROJECT_NAME}::${TARGET} ALIAS ${TARGET} )
install(
    TARGETS ${TARGET}
    EXPORT ${TARGETS_CONFIG_FILENAME}
    RUNTIME DESTINATION bin COMPONENT bin
    LIBRARY DESTINATION "${LIB_PATH}" COMPONENT bin
    ARCHIVE DESTINATION "${LIB_PATH}" COMPONENT dev
)

install(
    DIRECTORY ${INCLUDE_PATH}
    DESTINATION include
)

install(
    EXPORT ${TARGETS_CONFIG_FILENAME} NAMESPACE ${PROJECT_NAME}:: COMPONENT dev
    DESTINATION "${SHARE_PATH}/cmake/"
)

# Write package configuration version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${LEAFY_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" @ONLY)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${SHARE_PATH}/cmake/"
)

# Export config files and package
export(EXPORT ${TARGETS_CONFIG_FILENAME} NAMESPACE ${PROJECT_NAME}::)
export(PACKAGE ${PROJECT_NAME})
