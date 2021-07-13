#ifndef _LOG_MESSAGE_H
#define _LOG_MESSAGE_H

#include <chrono>
#include <cstdint>
#include <string>
#include <string_view>

#include "common.hpp"

struct LogMsg
{
	LogMsg(const std::string_view &category, LogLevel level, std::string &&text);

	std::string_view category;
	std::string_view text;
	std::chrono::zoned_time<std::chrono::system_clock::duration> time;
	LogLevel level;
};

#endif // _LOG_MESSAGE_H
