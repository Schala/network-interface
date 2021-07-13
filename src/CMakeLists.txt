configure_file (config.h.in ${CMAKE_BINARY_DIR}/src/config.h)

set (CORE_SOURCES
	connection.hpp
	owned_msg.hpp
	server.hpp
	tsqueue.hpp
)

if (SQLITE_FRONTEND)
endif ()

if (MYSQL_FRONTEND)
endif ()

add_library (cmmnet_core ${CORE_SOURCES})
target_include_directories (cmmnet_core PUBLIC ${CMAKE_BINARY_DIR}/src)
target_include_directories (cmmnet_core PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries (cmmnet_core cmmnet_logging)
set_target_properties (cmmnet_core PROPERTIES LINKER_LANGUAGE CXX)

if (SQLITE_FRONTEND)
	target_include_directories (cmmnet_core PRIVATE ${SQLite3_INCLUDE_DIRS})
endif ()

if (MYSQL_FRONTEND)
	target_include_directories (cmmnet_core PRIVATE ${MariaDBClient_INCLUDE_DIRS})
endif ()

add_subdirectory (kdx)
add_subdirectory (logging)
#add_subdirectory (palace)
