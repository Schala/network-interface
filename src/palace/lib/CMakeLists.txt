if (BUILD_PALACE)
	set (PALACE_LIB_SOURCES
		asset.cpp
		codec.cpp
		connection.cpp
		message.cpp
		protocol.cpp
	)

	add_library (Palace ${PALACE_LIB_SOURCES})

	if (WIN32)
		target_link_libraries (Palace wsock32 ws2_32)
	endif ()
endif ()
