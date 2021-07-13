#include "appender.hpp"
#include "logger.hpp"
#include "message.hpp"

Logger::Logger(const std::string &name, LogLevel level):
	m_name(name),
	m_level(level)
{
}

Logger::~Logger()
{
	for (auto &[k, v] : m_appenders)
		 delete v;
}

std::string& Logger::GetName()
{
	return m_name;
}

LogLevel Logger::GetLevel() const
{
	return m_level;
}

void Logger::SetLevel(LogLevel level)
{
	m_level = level;
}

void Logger::AddAppender(uint8_t id, LogAppender *appender)
{
	m_appenders[id] = appender;
}

void Logger::RemoveAppender(uint8_t id)
{
	m_appenders.erase(id);
}

void Logger::Write(const LogMsg &msg)
{
	for (auto &[k, v] : m_appenders)
		if (v) v->Write(msg);
}