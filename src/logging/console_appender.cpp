#include "console_appender.hpp"

ConsoleLogAppender::ConsoleLogAppender(std::wostream &stream, const LogAppenderFlags &flags,
		LogLevel level):
	LogAppender(flags, level),
	m_stream(stream)
{
}

void ConsoleLogAppender::OnWrite(const std::wstring &msg)
{
	m_stream << msg;
}
