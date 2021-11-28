##############################
######					######
###### 	URL Shortener	######
######					######
##############################

cmake_minimum_required(VERSION 3.14.0)

if(NOT APPLE)
	message(FATAL_ERROR "Unfortunetly only MacOS is supported.")
endif()

set(MACOSX_COMPILER "libcxx-min10.14")
set(MACOSX_SYSTEM_ID "MacOSX-x86-64")

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
	set(THIRDPARTY_LOCATION "${CMAKE_INSTALL_PREFIX}/ThirdPartyDependencies")
	if(NOT EXISTS ${THIRDPARTY_LOCATION})
		if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Auxiliary/ThirdPartyDependencies.tar.gz")
			message(STATUS "Unpacking 3rd party dependencies...")
			execute_process(
				COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/Auxiliary/ThirdPartyDependencies.tar.gz"
				WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
			)
		endif()
	endif()

	#=============================================
	#==================== ZLIB ===================
	#=============================================
	find_library(Z_LIBRARY
		NAMES z
	)
	if(${Z_LIBRARY} STREQUAL Z_LIBRARY-NOTFOUND)
		message(FATAL_ERROR "libz not found.")
	endif()

	#=============================================
	#=================== Served ==================
	#=============================================
	list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

	set(SERVED_VERSION "1.0.0")

	set(SERVED_BINARY_LOCATION "${THIRDPARTY_LOCATION}/Served/${SERVED_VERSION}/${MACOSX_SYSTEM_ID}/${MACOSX_COMPILER}/Lib")
	set(SERVED_INCLUDE_LOCATION "${THIRDPARTY_LOCATION}/Served/${SERVED_VERSION}/${MACOSX_SYSTEM_ID}/${MACOSX_COMPILER}/Include")

	include_directories(${SERVED_INCLUDE_LOCATION})

	find_library(SERVED_LIBRARY
		NAMES served
		PATHS ${SERVED_BINARY_LOCATION}
		NO_DEFAULT_PATH
	)
	if(${SERVED_LIBRARY} STREQUAL SERVED_LIBRARY-NOTFOUND)
		message(FATAL_ERROR "libserved.a not found.")
	endif()

	#=============================================
	#================== Crypto++ =================
	#=============================================
	list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

	set(CRYPTO_VERSION "8.6")

	set(CRYPTO_BINARY_LOCATION "${THIRDPARTY_LOCATION}/Crypto++/${CRYPTO_VERSION}/${MACOSX_SYSTEM_ID}/${MACOSX_COMPILER}/Lib")
	set(CRYPTO_INCLUDE_LOCATION "${THIRDPARTY_LOCATION}/Crypto++/${CRYPTO_VERSION}/${MACOSX_SYSTEM_ID}/${MACOSX_COMPILER}/Include")

	include_directories(${CRYPTO_INCLUDE_LOCATION})

	find_library(CRYPTO_LIBRARY
		NAMES cryptopp
		PATHS ${CRYPTO_BINARY_LOCATION}
		NO_DEFAULT_PATH
	)
	if(${CRYPTO_LIBRARY} STREQUAL CRYPTO_LIBRARY-NOTFOUND)
		message(FATAL_ERROR "libcryptopp.a not found.")
	endif()

	#=============================================
	#=================== Boost ===================
	#=============================================
	list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

	set(BOOST_VERSION "1.78.0")

	set(BOOST_BINARY_LOCATION "${THIRDPARTY_LOCATION}/Boost/${BOOST_VERSION}/${MACOSX_SYSTEM_ID}/${MACOSX_COMPILER}/Lib")
	set(BOOST_INCLUDE_LOCATION "${THIRDPARTY_LOCATION}/Boost/${BOOST_VERSION}/${MACOSX_SYSTEM_ID}/${MACOSX_COMPILER}/Include")

	include_directories(${BOOST_INCLUDE_LOCATION})

	find_library(BOOST-JSON_LIBRARY
		NAMES boost_json
		PATHS ${BOOST_BINARY_LOCATION}
		NO_DEFAULT_PATH
	)
	if(${BOOST-JSON_LIBRARY} STREQUAL BOOST-JSON_LIBRARY-NOTFOUND)
		message(FATAL_ERROR "libboost_json.a not found.")
	endif()

	find_library(BOOST-UNIT-TEST_LIBRARY
		NAMES boost_unit_test_framework
		PATHS ${BOOST_BINARY_LOCATION}
		NO_DEFAULT_PATH
	)
	if(${BOOST-UNIT-TEST_LIBRARY} STREQUAL BOOST-UNIT-TEST_LIBRARY-NOTFOUND)
		message(FATAL_ERROR "libboost_unit_test_framework.a not found.")
	endif()

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

	include(${CMAKE_CURRENT_SOURCE_DIR}/Tests/Tests.cmake)
	setup_test_target(TRUE)

endif() #end IF NOT TARGET URLShortener
