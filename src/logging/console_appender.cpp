#include "console_appender.hpp"

ConsoleLogAppender::ConsoleLogAppender(std::ostream &stream, const LogAppenderFlags &flags,
		LogLevel level):
	LogAppender(flags, level),
	m_stream(stream)
{
}

ConsoleLogAppender::~ConsoleLogAppender()
{
	Close();
}

void ConsoleLogAppender::Close()
{
	m_stream << "\033[0m";
}

void ConsoleLogAppender::OnBeginFormat(std::string &text, const LogMsg &msg)
{
	if (!m_flags.colour) return;

	switch (msg.level)
	{
		case LogLevel::Fatal: text += "\033[41m"; break;
		case LogLevel::Error: text += "\033[91m"; break;
		case LogLevel::Warning: text += "\033[93m"; break;
		case LogLevel::Debug: text += "\033[92m"; break;
		default: text += "\033[0m";
	};
}

void ConsoleLogAppender::OnWrite(const std::string &msg)
{
	m_stream << msg;
}
