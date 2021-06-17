add_subdirectory (lib)

set (PALACE_SERVER_SOURCES
	server.cpp
)

add_executable(PalaceServer ${PALACE_SERVER_SOURCES})
target_link_libraries (PalaceServer Palace ${OpenSSL_CRYPTO_LIBRARIES})

if (WIN32)
	target_link_libraries (PalaceServer wsock32 ws2_32)
endif ()
