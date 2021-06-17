configure_file (config.h.in ${CMAKE_BINARY_DIR}/src/config.h)

set (LIB_SOURCES "")

if (SQLITE_BACKEND)
	list (APPEND ${LIB_SOURCES} tssqlite.cpp)
endif ()

if (MYSQL_BACKEND)
	list (APPEND ${LIB_SOURCES} tsmysql.cpp)
endif ()

if (${LIB_SOURCES})
	add_library (cmmnet ${LIB_SOURCES})

	if (SQLITE_BACKEND)
		target_link_libraries (cmmnet ${SQLite3_LIBRARIES})
	endif ()

	if (MYSQL_BACKEND)
		target_link_libraries (cmmnet ${MariaDBClient_LIBRARIES})
	endif ()
endif ()

add_subdirectory (kdx)
add_subdirectory (palace)
