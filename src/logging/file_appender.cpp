#include "file_appender.hpp"

FileLogAppender::FileLogAppender(const std::filesystem::path &path, const LogAppenderFlags &flags,
		LogLevel level):
	LogAppender(flags, level),
	m_stream(std::ofstream(path))
{
}

FileLogAppender::~FileLogAppender()
{
	Close();
}

void FileLogAppender::Close()
{
	m_stream.close();
}

void FileLogAppender::OnWrite(const std::string &msg)
{
	m_stream << msg;
}
