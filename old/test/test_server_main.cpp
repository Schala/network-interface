#include <iostream>

#include "../src/logging/console_appender.hpp"
#include "../src/logging/file_appender.hpp"
#include "test_server.hpp"

int main(int argc, char **argv)
{
	ConsoleLogAppender clog(std::cout, { 0, 1 }, LogLevel::Debug);
	FileLogAppender flog("testserver.log", {0, 1}, LogLevel::Debug);
	S_LOG.AddAppender(&clog);
	S_LOG.AddAppender(&flog);
	TestServer srv(6666);
	srv.Start();

	while (1)
		srv.Update();
		
	return 0;
}
