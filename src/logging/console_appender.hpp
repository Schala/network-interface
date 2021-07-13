#ifndef _LOG_CONSOLE_APPENDER_H
#define _LOG_CONSOLE_APPENDER_H

#include <ostream>

#include "appender.hpp"

class ConsoleLogAppender : public LogAppender
{
public:
	ConsoleLogAppender(std::ostream &stream, const LogAppenderFlags &flags, LogLevel level);
	~ConsoleLogAppender();
	void Close();
private:
	std::ostream &m_stream;
	
	void OnBeginFormat(std::string &text, const LogMsg &msg);
	void OnWrite(const std::string &msg);
};

#endif // _LOG_CONSOLE_APPENDER_H
