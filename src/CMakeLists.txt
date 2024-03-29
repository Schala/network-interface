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
	macros.h
	netqueue.hpp
	netset.hpp
	packet.hpp
	server.hpp
	session.hpp
)

if (SQLITE_BACKEND)
	list (APPEND CORE_SOURCES
		sqlite/prepared_result.cpp
		sqlite/prepared_result.hpp
		sqlite/result.cpp
		sqlite/result.hpp
	)
endif ()

add_library (cmmnet_core ${CORE_SOURCES})
target_include_directories (cmmnet_core PUBLIC ${CMAKE_BINARY_DIR}/src)
target_include_directories (cmmnet_core PRIVATE ${Boost_INCLUDE_DIRS})
set_target_properties (cmmnet_core PROPERTIES LINKER_LANGUAGE CXX)

if (SQLITE_BACKEND)
	target_include_directories (cmmnet_core PRIVATE ${SQLite3_INCLUDE_DIRS})
endif ()

add_subdirectory (_3rdparty)
add_subdirectory (hl)
