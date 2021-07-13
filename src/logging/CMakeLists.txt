set (LOGGING_SOURCES
	appender.cpp
	appender.hpp
	common.hpp
	console_appender.cpp
	console_appender.hpp
	file_appender.cpp
	file_appender.hpp
	log.cpp
	log.hpp
	logger.cpp
	logger.hpp
	message.cpp
	message.hpp
)

add_library (cmmnet_logging ${LOGGING_SOURCES})
target_include_directories (cmmnet_logging PUBLIC ${CMAKE_BINARY_DIR}/src)
