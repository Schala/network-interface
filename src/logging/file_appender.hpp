#ifndef _LOG_FILE_APPENDER_H
#define _LOG_FILE_APPENDER_H

#include <filesystem>
#include <fstream>

#include "appender.hpp"

class FileLogAppender : public LogAppender
{
public:
	FileLogAppender(const std::filesystem::path &path, const LogAppenderFlags &flags, LogLevel level);
	~FileLogAppender();
	void Close();
private:
	std::ofstream m_stream;

	void OnWrite(const std::string &msg);
};

#endif // _LOG_FILE_APPENDER_H
