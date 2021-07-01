add_subdirectory (lib)

set (PALACE_SERVER_SOURCES
	dbworker.cpp
	dbworker.hpp
	server.cpp
	server.hpp
)

add_executable(PalaceServer ${PALACE_SERVER_SOURCES})
target_link_libraries (PalaceServer Palace)
target_link_libraries (PalaceServer ${OpenSSL_CRYPTO_LIBRARIES})
target_link_libraries (PalaceServer ${SQLite3_LIBRARIES})
target_include_directories (PalaceServer PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories (PalaceServer PUBLIC ${CMAKE_SOURCE_DIR}/src)

if (WIN32)
	target_link_libraries (PalaceServer wsock32 ws2_32)
endif ()
