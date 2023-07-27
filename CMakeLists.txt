cmake_minimum_required(VERSION 3.21)

set( LEAFY_MAJOR_VERSION 0 )
set( LEAFY_MINOR_VERSION 1 )
set( LEAFY_REVISION_VERSION 0 )
set( LEAFY_VERSION ${LEAFY_MAJOR_VERSION}.${LEAFY_MINOR_VERSION}.${LEAFY_REVISION_VERSION} )

project( leafy LANGUAGES CXX VERSION ${LEAFY_VERSION} )
set( TARGET ${PROJECT_NAME} )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

find_package( OpenGL REQUIRED )

if( NOT OPENGL_FOUND )
    message("Missing OpenGL" FATAL_ERROR)
endif()

if( NOT TARGET sfml-graphics )
    find_package( SFML 2.5 REQUIRED COMPONENTS graphics window system network audio )
endif()

if ( NOT SFML_FOUND )
    message("Unable to locate SFML - Fetching content for local install")
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif()

set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )

file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.hpp" )
file( GLOB_RECURSE INLS "${INCLUDE_PATH}/*.inl")
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

# Set the library output directory
set( LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib" )

add_executable( ${TARGET} ${CPPS} ${INLS} ${HPPS} )

target_link_libraries( ${TARGET} PUBLIC sfml-graphics sfml-window sfml-system sfml-network sfml-audio ${OPENGL_gl_LIBRARY} )

if( WIN32 )
    target_compile_definitions( ${TARGET} PRIVATE WIN32 )
elseif( APPLE )
    find_library( FOUNDATION_FRAMEWORK Foundation REQUIRED)
    find_library( COREGRAPHICS_FRAMEWORK CoreGraphics REQUIRED)
    
    target_link_libraries( ${TARGET} PUBLIC ${FOUNDATION_FRAMEWORK} ${COREGRAPHICS_FRAMEWORK} )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
    find_package( X11 REQUIRED )

    target_link_libraries( ${TARGET} PUBLIC ${X11_LIBRARIES} )
endif()

if( CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options( ${TARGET} PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic )
endif()

install(
    TARGETS ${TARGET}
    CONFIGURATIONS Release
    RUNTIME DESTINATION
)

install(
    DIRECTORY ${INCLUDE_PATH}
    DESTINATION include
)
