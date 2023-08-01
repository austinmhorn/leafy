# This script locates the leafy library
# ------------------------------------
#
# Usage
# -----
#
# You can enforce a specific version, one of either MAJOR.MINOR.REVISION,
# MAJOR.MINOR or only MAJOR. If nothing is specified, the version won't
# be checked i.e. any version will be accepted. leafy does not consist of
# multiple components, so specifying COMPONENTS is not required.
#
# Example:
#   find_package( leafy )       // no specific version
#   find_package( leafy 0.2 )   // any 0.2 version
#   find_package( leafy 0.2.3 ) // version 0.2.3 or greater
#
# By default, the dynamic version of leafy will be found. To find the static
# version instead, you must set the LEAFY_STATIC_LIBRARIES variable to TRUE
# before calling find_package( leafy ). In that case, LEAFY_STATIC will also be
# defined by this script.
#
# Example:
#   set( LEAFY_STATIC_LIBRARIES TRUE )
#   find_package( leafy )
#
# Since you have to link all of leafy's dependencies when you link leafy
# statically, the variable LEAFY_DEPENDENCIES is also defined. See below
# for a detailed description.
#
# On Mac OS X if LEAFY_STATIC_LIBRARIES is not set to TRUE then by default CMake
# will search for frameworks unless CMAKE_FIND_FRAMEWORK is set to "NEVER".
# Please refer to CMake documentation for more details.
# Moreover, keep in mind that leafy frameworks are only available as release
# libraries unlike dylibs which are available for both release and debug modes.
#
# If leafy is not installed in a standard path, you can use the LEAFY_ROOT
# CMake (or environment) variable to tell CMake where to look for leafy.
#
# Output
# ------
#
# This script defines the following variables:
#   - LEAFY_LIBRARY_DEBUG:   the path to the debug library
#   - LEAFY_LIBRARY_RELEASE: the path to the release library
#   - LEAFY_LIBRARY:         the path to the library to link to
#   - LEAFY_FOUND:           TRUE if the leafy library is found
#   - LEAFY_INCLUDE_DIR:     the path where leafy headers are located (the directory containing the leafy/Config.hpp file)
#   - LEAFY_DEPENDENCIES:    the list of libraries leafy depends on, in case of static linking
#
# Example (dynamic linking):
#   find_package( leafy REQUIRED )
#   include_directories( ${LEAFY_INCLUDE_DIR} )
#   add_executable( myapp ... )
#   target_link_libraries( myapp ${LEAFY_LIBRARY} ... )
#
# Example (static linking):
#   set( LEAFY_STATIC_LIBRARIES TRUE )
#   find_package( LEAFY REQUIRED )
#   include_directories( ${LEAFY_INCLUDE_DIR} )
#   add_executable( myapp ... )
#   target_link_libraries( myapp ${LEAFY_LIBRARY} ${LEAFY_DEPENDENCIES} ... )

if( LEAFY_STATIC_LIBRARIES )
	add_definitions( -DLEAFY_STATIC )
endif()

set(
	LEAFY_SEARCH_PATHS
	"${LEAFY_ROOT}"
	"$ENV{LEAFY_ROOT}"
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)

find_path(
	LEAFY_INCLUDE_DIR
	leafy/Config.hpp
	PATH_SUFFIXES
		include
	PATHS
		${LEAFY_SEARCH_PATHS}
)

set( LEAFY_VERSION_OK true )
if( LEAFY_FIND_VERSION AND LEAFY_INCLUDE_DIR )
	file( READ "${LEAFY_INCLUDE_DIR}/leafy/Config.hpp" LEAFY_CONFIG_HPP )
	
	string( REGEX MATCH ".*#define LEAFY_MAJOR_VERSION ([0-9]+).*#define LEAFY_MINOR_VERSION ([0-9]+).*#define LEAFY_REVISION_VERSION ([0-9]+).*" LEAFY_CONFIG_HPP "${LEAFY_CONFIG_HPP}" )
	string( REGEX REPLACE ".*#define LEAFY_MAJOR_VERSION ([0-9]+).*" "\\1" LEAFY_VERSION_MAJOR "${LEAFY_CONFIG_HPP}" )
	string( REGEX REPLACE ".*#define LEAFY_MINOR_VERSION ([0-9]+).*" "\\1" LEAFY_VERSION_MINOR "${LEAFY_CONFIG_HPP}" )
	string( REGEX REPLACE ".*#define LEAFY_REVISION_VERSION ([0-9]+).*" "\\1" LEAFY_VERSION_PATCH "${LEAFY_CONFIG_HPP}" )
	
	math( EXPR LEAFY_REQUESTED_VERSION "${LEAFY_FIND_VERSION_MAJOR} * 10000 + ${LEAFY_FIND_VERSION_MINOR} * 100 + ${LEAFY_FIND_VERSION_PATCH}" )

	if( LEAFY_VERSION_MAJOR OR LEAFY_VERSION_MINOR OR LEAFY_VERSION_PATCH )
		math( EXPR LEAFY_VERSION "${LEAFY_VERSION_MAJOR} * 10000 + ${LEAFY_VERSION_MINOR} * 100 + ${LEAFY_VERSION_PATCH}" )

		if( LEAFY_VERSION LESS LEAFY_REQUESTED_VERSION )
			set( LEAFY_VERSION_OK false )
		endif()
	else()
		# LEAFY version is < 0.3.0
		if( LEAFY_REQUESTED_VERSION GREATER 300 )
			set( LEAFY_VERSION_OK false )
			set( LEAFY_VERSION_MAJOR 0 )
			set( LEAFY_VERSION_MINOR x )
			set( LEAFY_VERSION_PATCH y )
		endif()
	endif()
endif()

find_library(
	LEAFY_LIBRARY_DYNAMIC_RELEASE
	NAMES
		leafy
		Leafy
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		${LEAFY_SEARCH_PATHS}
)

find_library(
	LEAFY_LIBRARY_DYNAMIC_DEBUG
	NAMES
		leafy-d
		Leafy-d
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		${LEAFY_SEARCH_PATHS}
)

find_library(
	LEAFY_LIBRARY_STATIC_RELEASE
	NAMES
		leafy-s
		Leafy-s
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		${LEAFY_SEARCH_PATHS}
)

find_library(
	LEAFY_LIBRARY_STATIC_DEBUG
	NAMES
		leafy-s-d
		Leafy-s-d
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		${LEAFY_SEARCH_PATHS}
)

if( LEAFY_STATIC_LIBRARIES )
	if( LEAFY_LIBRARY_STATIC_RELEASE )
		set( LEAFY_LIBRARY_RELEASE "${LEAFY_LIBRARY_STATIC_RELEASE}" )
	endif()
	if( LEAFY_LIBRARY_STATIC_DEBUG )
		set( LEAFY_LIBRARY_DEBUG "${LEAFY_LIBRARY_STATIC_DEBUG}" )
	endif()
else()
	if( LEAFY_LIBRARY_DYNAMIC_RELEASE )
		set( LEAFY_LIBRARY_RELEASE "${LEAFY_LIBRARY_DYNAMIC_RELEASE}" )
	endif()
	if( LEAFY_LIBRARY_DYNAMIC_DEBUG )
		set( LEAFY_LIBRARY_DEBUG "${LEAFY_LIBRARY_DYNAMIC_DEBUG}" )
	endif()
endif()

mark_as_advanced(
	LEAFY_LIBRARY_STATIC_RELEASE
	LEAFY_LIBRARY_STATIC_DEBUG
	LEAFY_LIBRARY_DYNAMIC_RELEASE
	LEAFY_LIBRARY_DYNAMIC_DEBUG
)

if( LEAFY_LIBRARY_RELEASE OR LEAFY_LIBRARY_DEBUG )
	if( LEAFY_LIBRARY_RELEASE AND LEAFY_LIBRARY_DEBUG )
		set( LEAFY_LIBRARY debug "${LEAFY_LIBRARY_DEBUG}" optimized "${LEAFY_LIBRARY_RELEASE}" )
	elseif( LEAFY_LIBRARY_DEBUG AND NOT LEAFY_LIBRARY_RELEASE )
		set( LEAFY_LIBRARY_RELEASE "${LEAFY_LIBRARY_DEBUG}" )
		set( LEAFY_LIBRARY "${LEAFY_LIBRARY_DEBUG}" )
	elseif( LEAFY_LIBRARY_RELEASE AND NOT LEAFY_LIBRARY_DEBUG )
		set( LEAFY_LIBRARY_DEBUG "${LEAFY_LIBRARY_RELEASE}" )
		set( LEAFY_LIBRARY "${LEAFY_LIBRARY_RELEASE}" )
	endif()

	set( LEAFY_FOUND true )
else()
	set( LEAFY_LIBRARY "" )
	set( LEAFY_FOUND false )
endif()

mark_as_advanced(
	LEAFY_LIBRARY
	LEAFY_LIBRARY_RELEASE
	LEAFY_LIBRARY_DEBUG
)

if( LEAFY_STATIC_LIBRARIES )
	set( LEAFY_DEPENDENCIES )
	set( LEAFY_MISSING_DEPENDENCIES )

	if( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
		find_library( X11_LIBRARY NAMES X11 PATHS ${LEAFY_SEARCH_PATHS} PATH_SUFFIXES lib )
		
		if( ${X11_LIBRARY} STREQUAL "X11_LIBRARY-NOTFOUND" )
			unset( X11_LIBRARY )
			set( LEAFY_MISSING_DEPENDENCIES "${LEAFY_MISSING_DEPENDENCIES} X11" )
		endif()
	endif()

	if( "${CMAKE_SYSTEM_NAME}" MATCHES "Windows" )
		set( LEAFY_DEPENDENCIES ${LEAFY_DEPENDENCIES} "opengl32" )
	elseif( ( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" ) OR ( "${CMAKE_SYSTEM_NAME}" MATCHES "FreeBSD" ) )
		set( LEAFY_DEPENDENCIES ${LEAFY_DEPENDENCIES} "GL" ${X11_LIBRARY} )
	elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )
		set( LEAFY_DEPENDENCIES ${LEAFY_DEPENDENCIES} "-framework OpenGL -framework Foundation" )
	endif()
endif()

if( NOT LEAFY_INCLUDE_DIR OR NOT LEAFY_LIBRARY )
	set( LEAFY_FOUND false )
endif()

if( NOT LEAFY_FOUND )
	set( FIND_LEAFY_ERROR "LEAFY not found." )
elseif( NOT LEAFY_VERSION_OK )
	set( FIND_LEAFY_ERROR "LEAFY found but version too low, requested: ${LEAFY_FIND_VERSION}, found: ${LEAFY_VERSION_MAJOR}.${LEAFY_VERSION_MINOR}.${LEAFY_VERSION_PATCH}" )
	set( LEAFY_FOUND false )
elseif( LEAFY_STATIC_LIBRARIES AND LEAFY_MISSING_DEPENDENCIES )
	set( FIND_LEAFY_ERROR "LEAFY found but some of its dependencies are missing: ${LEAFY_MISSING_DEPENDENCIES}" )
	set( LEAFY_FOUND false )
endif()

if( NOT LEAFY_FOUND )
	if( LEAFY_FIND_REQUIRED )
		message( FATAL_ERROR "${FIND_LEAFY_ERROR}" )
	elseif( NOT LEAFY_FIND_QUIETLY )
		message( "${FIND_LEAFY_ERROR}" )
	endif()
else()
	if( LEAFY_FIND_VERSION )
		message( STATUS "Found LEAFY version ${LEAFY_VERSION_MAJOR}.${LEAFY_VERSION_MINOR}.${LEAFY_VERSION_PATCH} in ${LEAFY_INCLUDE_DIR}" )
	else()
		message( STATUS "Found LEAFY in ${LEAFY_INCLUDE_DIR}" )
	endif()
endif()
