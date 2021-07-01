#include <iomanip>
#include <sstream>
#include <uchar.h>

#include "appender.hpp"
#include "message.hpp"

constexpr std::wstring_view LogAppender::GetLevelStr(LogLevel level)
{
	using namespace std::string_view_literals;

	switch (level)
	{
		case LogLevel::Warning: return L"[WARNING]\t"sv;
		case LogLevel::Error: return L"[ERROR]\t"sv;
		case LogLevel::Fatal: return L"[FATAL]\t"sv;
		case LogLevel::Debug: return L"[DEBUG]\t"sv;
		default: return L""sv;
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

	std::wostringstream ss;

	ss << GetLevelStr(msg.level) << std::put_time(&msg.time, L"%F %T - ");
	ss << msg.text << std::endl;

	OnWrite(ss.str());
}
