#include <iostream>

#include "console_appender.hpp"
#include "file_appender.hpp"
#include "log.hpp"
#include "logger.hpp"

int main()
{
	LogAppenderFlags flags { 0, 1 };
	ConsoleLogAppender clog(std::wcout, flags, LogLevel::Debug);
	FileLogAppender flog("test.log", flags, LogLevel::Debug);
	S_LOG.AddAppender(&clog);
	S_LOG.AddAppender(&flog);
	S_LOG.WriteMsg("Test", LogLevel::Debug, "hello world");
}
