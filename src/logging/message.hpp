#ifndef _LOG_MESSAGE_H
#define _LOG_MESSAGE_H

#include <ctime>
#include <cstdint>
#include <string>

#include "common.hpp"

enum class LogCategory : uint8_t
{
	Server,
	User,
	Room,
	Database,
	Asset,
	Script,
	Debug
};

struct LogMsg
{
	LogMsg(LogLevel level, std::wstring &&text);

	std::wstring text;
	std::tm time;
	LogLevel level;
	LogCategory category;
};

#endif // _LOG_MESSAGE_H
