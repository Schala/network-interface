#ifndef _LOG_H
#define _LOG_H

#include <filesystem>
#include <memory>
#include <utility>

#include "common.hpp"
#include "logger.hpp"
#include "message.hpp"

class Log
{
public:
	static Log& Get();
	
	void WriteMsg(LogCategory category, LogLevel level, std::wstring &&msg);
	void SetLowestLevel(LogLevel level);
	void SetLogger(const Logger &logger);
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
