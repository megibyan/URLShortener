##############################
######					######
###### 	URL Shortener	######
######					######
##############################

cmake_minimum_required(VERSION 3.14.0)

if(NOT APPLE)
	message(FATAL_ERROR "Unfortunetly only MacOS is supported.")
endif()

project(URLShortener
	VERSION		0.0.1
	DESCRIPTION	"A simple API to parse long URL to a shorter version, and retrieve the longer version from the latter."
	LANGUAGES	CXX
)

set(PROJECT_NAME URLShortener)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "Install prefix" FORCE)
endif()

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "None" "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

set(CMAKE_VERBOSE_MAKEFILE OFF CACHE BOOL "Verbose")

if(NOT TARGET URLShortener)
	#=============================================
	#============== MAIN LIBRARY =================
	#=============================================
	set_source_files_properties(
		PROPERTIES
		EXTERNAL_OBJECT true
		GENERATED true
	)

	include(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Sources.cmake)
	setup_url_target(FALSE)
	setup_url_target(TRUE)

endif() #end IF NOT TARGET URLShortener
