#include <utility>

#include "message.hpp"

LogMsg::LogMsg(const std::string_view &category, LogLevel level, std::string &&text):
	category(category),
	text(std::forward<std::string>(text)),
	time(std::chrono::current_zone(), std::chrono::system_clock::now()),
	level(level)
{
}
