if (BUILD_KDX AND BUILD_TESTS)
	include_directories (${CMAKE_SOURCE_DIR}/src)
	
	add_executable (test_kdx_codec test_kdx_codec.cpp)
	add_dependencies (test_kdx_codec KDX)
	target_link_libraries (test_kdx_codec KDX)
endif ()
