#ifndef _LOG_H
#define _LOG_H

#include <filesystem>
#include <string>

#include "logger.hpp"

class Log
{
public:
	static Log& Get();
	
	void WriteMsg(const std::string_view &category, LogLevel level, std::string &&msg);
	void SetLowestLevel(LogLevel level);
	void SetLogger(const Logger &logger);
	void AddAppender(LogAppender *appender);
	void RemoveAppender(uint8_t id);
private:
	std::filesystem::path m_path;
	Logger m_logger;
	LogLevel m_lowestLevel;
	uint8_t m_appenderID;

	Log();
	Log(const Log &) = delete;
	Log(Log &&) = delete;
	Log& operator=(const Log &) = delete;
	Log& operator=(Log &&) = delete;
};

#define S_LOG Log::Get()

#endif // _LOG_H
