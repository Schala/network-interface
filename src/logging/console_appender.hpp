#ifndef _LOG_CONSOLE_APPENDER_H
#define _LOG_CONSOLE_APPENDER_H

#include <ostream>

#include "appender.hpp"

class ConsoleLogAppender : public LogAppender
{
public:
	ConsoleLogAppender(std::wostream &stream, const LogAppenderFlags &flags, LogLevel level);
protected:
	std::wostream &m_stream;
private:
	void OnWrite(const std::wstring &msg);
};

#endif // _LOG_CONSOLE_APPENDER_H
