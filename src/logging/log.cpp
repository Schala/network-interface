#include <utility>

#include "log.hpp"
#include "logger.hpp"
#include "message.hpp"

Log& Log::Get()
{
	static Log singleton;
	return singleton;
}

Log::Log():
	m_lowestLevel(LogLevel::Fatal),
	m_logger("Default", m_lowestLevel),
	m_appenderID(0)
{
}

void Log::WriteMsg(const std::string_view &category, LogLevel level, std::string &&msg)
{
	LogMsg logMsg(category, level, std::move(msg));
	m_logger.Write(logMsg);
}

void Log::SetLowestLevel(LogLevel level)
{
	m_lowestLevel = level;
}

void Log::SetLogger(const Logger &logger)
{
	m_logger = logger;
}

void Log::AddAppender(LogAppender *appender)
{
	m_logger.AddAppender(m_appenderID++, appender);
}

void Log::RemoveAppender(uint8_t id)
{
	m_logger.RemoveAppender(id);
}
