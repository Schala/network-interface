add_subdirectory (kdx)
#add_subdirectory (palace)

if (BUILD_TESTS)
	include_directories (${CMAKE_SOURCE_DIR}/src)

	add_executable (test_server test_server_main.cpp test_server.hpp test_connection.hpp)
	add_dependencies (test_server cmmnet_core)
	target_link_libraries (test_server cmmnet_core)
	target_include_directories (test_server PRIVATE ${Boost_INCLUDE_DIRS})

	add_executable (test_client test_client.cpp test_connection.hpp)
	add_dependencies (test_client cmmnet_core)
	target_include_directories (test_client PRIVATE ${Boost_INCLUDE_DIRS})

	if (WIN32)
		target_link_libraries (test_client wsock32 ws2_32)
		target_link_libraries (test_server wsock32 ws2_32)
	endif ()
endif ()
