add_subdirectory (kdx)
#add_subdirectory (palace)

if (BUILD_TESTS)
	include_directories (${CMAKE_SOURCE_DIR}/src)

	add_executable (test_server test_server_main.cpp test_server.hpp)
	target_link_libraries (test_server cmmnet_logging)
	target_include_directories (test_server PRIVATE ${Boost_INCLUDE_DIRS})
	if (WIN32)
		target_link_libraries (test_server wsock32 ws2_32)
	endif ()
endif ()
