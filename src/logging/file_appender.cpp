#include "file_appender.hpp"

FileLogAppender::FileLogAppender(std::wofstream &stream, const LogAppenderFlags &flags,
		LogLevel level):
	ConsoleLogAppender(stream, flags, level)
{
}

FileLogAppender::~FileLogAppender()
{
	Close();
}

void FileLogAppender::Close()
{
	dynamic_cast<std::wofstream *>(&m_stream)->close();
}
