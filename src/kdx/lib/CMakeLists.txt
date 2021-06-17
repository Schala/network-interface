if (BUILD_KDX)
	set (KDX_LIB_SOURCES
		codec.cpp
		tscodec.cpp
	)

	add_library (KDX ${KDX_LIB_SOURCES})
	target_include_directories (KDX PUBLIC ${CMAKE_BINARY_DIR}/src)
endif ()
