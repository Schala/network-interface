#include "log.hpp"
#include <iostream>

Log& Log::Get()
{
	static Log singleton;
	return singleton;
}

Log::Log():
	m_lowestLevel(LogLevel::Fatal),
	m_logger(L"Default", m_lowestLevel),
	m_appenderID(0)
{
}

void Log::WriteMsg(LogCategory category, LogLevel level, std::wstring &&msg)
{
	LogMsg logMsg(level, std::move(msg));
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
