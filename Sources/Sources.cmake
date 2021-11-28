function(gather_includes URLShortener_SOURCE_FILES)
	set(URLShortener_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Sources)

	set(URLShortener_Source_FILES
		${URLShortener_SOURCE_DIR}/main.cpp
	)
	source_group("" FILES ${URLShortener_Source_FILES})

	set(URLShortener_Internal_Crypto_FILES
		${URLShortener_SOURCE_DIR}/Internal/Crypto/CryptoEncoder.hpp
		${URLShortener_SOURCE_DIR}/Internal/Crypto/CryptoDecoder.hpp
		${URLShortener_SOURCE_DIR}/Internal/Crypto/CryptoUtilities.hpp
		${URLShortener_SOURCE_DIR}/Internal/Crypto/CryptoUtilities.cpp
	)
	source_group("Internal/Crypto" FILES ${URLShortener_Internal_Crypto_FILES})

	set(URLShortener_Internal_SHA256_FILES
		${URLShortener_SOURCE_DIR}/Internal/Crypto/SHA256/SHA256.hpp
		${URLShortener_SOURCE_DIR}/Internal/Crypto/SHA256/SHA256.cpp
	)
	source_group("Internal/Crypto/SHA256" FILES ${URLShortener_Internal_SHA256_FILES})

	set(URLShortener_Internal_Base62_FILES
		${URLShortener_SOURCE_DIR}/Internal/Crypto/Base62/Base62.hpp
		${URLShortener_SOURCE_DIR}/Internal/Crypto/Base62/Base62.cpp
	)
	source_group("Internal/Crypto/Base62" FILES ${URLShortener_Internal_Base62_FILES})

	set(URLShortener_Internal_CRC32_FILES
		${URLShortener_SOURCE_DIR}/Internal/Crypto/CRC32/CRC32.hpp
		${URLShortener_SOURCE_DIR}/Internal/Crypto/CRC32/CRC32.cpp
	)
	source_group("Internal/Crypto/CRC32" FILES ${URLShortener_Internal_CRC32_FILES})

	set(${URLShortener_SOURCE_FILES} 
		${URLShortener_Source_FILES}
		${URLShortener_Internal_Crypto_FILES}
		${URLShortener_Internal_SHA256_FILES}
		${URLShortener_Internal_Base62_FILES}
		${URLShortener_Internal_CRC32_FILES}
		PARENT_SCOPE
	)
endfunction()

function(setup_url_target EXECUTABLE)
	gather_includes(URLShortener_SOURCE_FILES)

	if (${EXECUTABLE})
		set(FINAL_TARGET "URLShortener")
		add_executable(${FINAL_TARGET} ${URLShortener_SOURCE_FILES})
	else()
		set(FINAL_TARGET "liburlshortener")
		add_library(${FINAL_TARGET} ${URLShortener_SOURCE_FILES})
	endif()

	set_target_properties(${FINAL_TARGET} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
		CXX_VISIBILITY_PRESET hidden
		INSTALL_RPATH "@loader_path/"
		COMPILE_FLAGS "-m64"
		LINK_FLAGS "-m64"
	)

	target_compile_options(${FINAL_TARGET}
		PRIVATE "-Wall"
		PRIVATE "-Wextra"
		PRIVATE "-fPIC"
		PRIVATE "-pipe"
		PRIVATE "-pedantic"
		PRIVATE "$<$<NOT:$<CONFIG:Debug>>:-O3>"
		PRIVATE "-Wno-deprecated-declarations"
	)
	target_compile_definitions(${FINAL_TARGET} PUBLIC _GLIBCXX_USE_CXX11_ABI=0)
	add_compile_definitions(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR=1)

	set_property(TARGET ${FINAL_TARGET} PROPERTY PREFIX "")

	target_link_libraries(${FINAL_TARGET} PUBLIC
		${Z_LIBRARY}
		${SERVED_LIBRARY}
		${CRYPTO_LIBRARY}
		${BOOST-JSON_LIBRARY}
		${BOOST-UNIT-TEST_LIBRARY}
	)

	target_include_directories(${FINAL_TARGET} PUBLIC
		"Sources/Internal/Crypto"
		"Sources/Internal/Crypto/SHA256"
		"Sources/Internal/Crypto/Base62"
		"Sources/Internal/Crypto/CRC32"
	)
endfunction()
