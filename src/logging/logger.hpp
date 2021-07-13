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
	Logger(const std::string &name, LogLevel level);
	~Logger();
	std::string& GetName();
	LogLevel GetLevel() const;
	void SetLevel(LogLevel level);
	void AddAppender(uint8_t id, LogAppender *appender);
	void RemoveAppender(uint8_t id);
	void Write(const LogMsg &msg);
private:
	std::string m_name;
	std::unordered_map<uint8_t, LogAppender *> m_appenders;
	LogLevel m_level;
};

#endif // _LOGGER_H
