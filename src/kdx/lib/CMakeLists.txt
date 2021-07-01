if (BUILD_KDX)
	set (KDX_LIB_SOURCES
		codec.cpp
		codec.hpp
		tscodec.cpp
		tscodec.hpp
	)

	add_library (KDX ${KDX_LIB_SOURCES})
	target_include_directories (KDX PUBLIC ${CMAKE_BINARY_DIR}/src)
	target_include_directories (KDX PUBLIC ${CMAKE_SOURCE_DIR}/src)
	target_include_directories (KDX PRIVATE ${Boost_INCLUDE_DIRS})
endif ()
