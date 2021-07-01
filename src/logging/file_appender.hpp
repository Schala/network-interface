#ifndef _LOG_FILE_APPENDER_H
#define _LOG_FILE_APPENDER_H

#include <fstream>

#include "console_appender.hpp"

class FileLogAppender : public ConsoleLogAppender
{
public:
	FileLogAppender(std::wofstream &stream, const LogAppenderFlags &flags, LogLevel level);
	~FileLogAppender();
	void Close();
};

#endif // _LOG_FILE_APPENDER_H
