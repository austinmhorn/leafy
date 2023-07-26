cmake_minimum_required(VERSION 3.21)

set( SFAF_MAJOR_VERSION 0 )
set( SFAF_MINOR_VERSION 1 )
set( SFAF_REVISION_VERSION 0 )
set( SFAF_VERSION ${SFAF_MAJOR_VERSION}.${SFAF_MINOR_VERSION}.${SFAF_REVISION_VERSION} )

project( sfaf LANGUAGES CXX VERSION ${SFAF_VERSION} )
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
    find_package( SFML 2.5 REQUIRED COMPONENTS graphics window system )
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

set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src/" )
file( GLOB_RECURSE HPPS "${SOURCE_PATH}/*.hpp" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

add_executable( ${TARGET} ${CPPS} ${HPPS} )

if( WIN32 )
    target_compile_definitions( ${TARGET} PRIVATE WIN32 )
elseif( SFAFLE )
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

target_link_libraries( ${TARGET} PRIVATE sfml-graphics sfml-window sfml-system sfml-system sfml-audio)

install(TARGETS ${TARGET}
        CONFIGURATIONS Release
        RUNTIME DESTINATION)
