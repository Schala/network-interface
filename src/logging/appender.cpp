#include <format>
#include <iostream>

#include "appender.hpp"
#include "message.hpp"

constexpr std::string_view LogAppender::GetLevelStr(LogLevel level)
{
	using namespace std::string_view_literals;

	switch (level)
	{
		case LogLevel::Warning: return "[WARNING]\t"sv;
		case LogLevel::Error: return "[ERROR]\t"sv;
		case LogLevel::Fatal: return "[FATAL]\t"sv;
		case LogLevel::Debug: return "[DEBUG]\t"sv;
		default: return ""sv;
	}
}

LogAppender::LogAppender(const LogAppenderFlags &flags, LogLevel level):
	m_flags(flags),
	m_level(level)
{
}

LogAppender::~LogAppender()
{
	Close();
}

void LogAppender::Close()
{
}

void LogAppender::Write(const LogMsg &msg)
{
	if (m_level < msg.level) return;

	std::string s = "";

	OnBeginFormat(s, msg);
	s += std::format("{} {:%F %X %p} {}\n", GetLevelStr(msg.level), msg.time, msg.text);
	OnWrite(s);
}

void LogAppender::OnBeginFormat(std::string &text, const LogMsg &msg)
{
}
