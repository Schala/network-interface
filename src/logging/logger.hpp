#ifndef _LOGGER_H
#define _LOGGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "common.hpp"

class LogAppender;
struct LogMsg;

class Logger
{
public:
	Logger(const std::wstring &name, LogLevel level);
	~Logger();
	std::wstring& GetName();
	LogLevel GetLevel() const;
	void SetLevel(LogLevel level);
	void AddAppender(uint8_t id, LogAppender *appender);
	void RemoveAppender(uint8_t id);
	Logger& Write(const LogMsg &msg);
private:
	std::wstring m_name;
	std::unordered_map<uint8_t, LogAppender *> m_appenders;
	LogLevel m_level;
};

#endif // _LOGGER_H
