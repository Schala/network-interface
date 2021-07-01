if (BUILD_PALACE)
	set (PALACE_LIB_SOURCES
		asset.cpp
		asset.hpp
		codec.cpp
		codec.hpp
		connection.cpp
		connection.hpp
		message.cpp
		message.hpp
		protocol.cpp
		protocol.hpp
		session.cpp
		session.hpp
	)

	add_library (Palace ${PALACE_LIB_SOURCES})
	target_include_directories (Palace PUBLIC ${CMAKE_BINARY_DIR}/src)
	target_include_directories (Palace PUBLIC ${CMAKE_SOURCE_DIR}/src)
	target_include_directories (Palace PRIVATE ${Boost_INCLUDE_DIRS})
endif ()
