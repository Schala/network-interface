configure_file (config.h.in ${CMAKE_BINARY_DIR}/src/config.h)

set (CORE_SOURCES
	logging/appender.cpp
	logging/appender.hpp
	logging/common.hpp
	logging/console_appender.cpp
	logging/console_appender.hpp
	logging/file_appender.cpp
	logging/file_appender.hpp
	logging/log.cpp
	logging/log.hpp
	logging/logger.cpp
	logging/logger.hpp
	logging/message.cpp
	logging/message.hpp
	client.hpp
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
set_target_properties (cmmnet_core PROPERTIES LINKER_LANGUAGE CXX)

if (SQLITE_FRONTEND)
	target_include_directories (cmmnet_core PRIVATE ${SQLite3_INCLUDE_DIRS})
endif ()

if (MYSQL_FRONTEND)
	target_include_directories (cmmnet_core PRIVATE ${MariaDBClient_INCLUDE_DIRS})
endif ()

add_subdirectory (kdx)
#add_subdirectory (palace)
