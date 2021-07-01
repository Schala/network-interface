configure_file (config.h.in ${CMAKE_BINARY_DIR}/src/config.h)

set (LIB_SOURCES
	connection.hpp
	owned_msg.hpp
	server.hpp
	tsqueue.hpp
)

if (SQLITE_FRONTEND)
endif ()

if (MYSQL_FRONTEND)
endif ()

add_library (cmmnet ${LIB_SOURCES})
target_include_directories (cmmnet PUBLIC ${CMAKE_BINARY_DIR}/src)
target_include_directories (cmmnet PRIVATE ${Boost_INCLUDE_DIRS})

if (SQLITE_FRONTEND)
	target_include_directories (cmmnet PRIVATE ${SQLite3_INCLUDE_DIRS})
endif ()

if (MYSQL_FRONTEND)
	target_include_directories (cmmnet PRIVATE ${MariaDBClient_INCLUDE_DIRS})
endif ()

add_subdirectory (kdx)
add_subdirectory (logging)
add_subdirectory (palace)
