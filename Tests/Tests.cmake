function(setup_test_target)
	enable_testing ()
	add_executable (Test
		Tests/Tests.cpp
	)

	set_target_properties(Test PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
		CXX_VISIBILITY_PRESET hidden
		INSTALL_RPATH "@loader_path/"
		COMPILE_FLAGS "-m64"
		LINK_FLAGS "-m64"
	)

	target_compile_options(Test
		PRIVATE "-Wall"
		PRIVATE "-Wextra"
		PRIVATE "-fPIC"
		PRIVATE "-pipe"
		PRIVATE "-pedantic"
		PRIVATE "$<$<NOT:$<CONFIG:Debug>>:-O3>"
		PRIVATE "-Wno-deprecated-declarations"
	)
	target_compile_definitions(Test PUBLIC _GLIBCXX_USE_CXX11_ABI=0)
	add_compile_definitions(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR=1)

	set_property(TARGET Test PROPERTY PREFIX "")

	target_link_libraries(Test
		${Z_LIBRARY}
		${SERVED_LIBRARY}
		${CRYPTO_LIBRARY}
		${BOOST-JSON_LIBRARY}
		${BOOST-UNIT-TEST_LIBRARY}
		"liburlshortener"
	)

	target_include_directories(Test PUBLIC
		"Sources/Internal/Crypto/Base62"
		"Sources/Internal/Crypto/CRC32"
		"Sources/Internal/Crypto/SHA256"
	)
endfunction()
