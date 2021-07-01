#include <chrono>
#include <utility>

#include "message.hpp"

LogMsg::LogMsg(LogLevel level, std::wstring &&text):
	text(std::forward<std::wstring>(text)),
	level(level)
{
	using namespace std::chrono;

	std::time_t now = system_clock::to_time_t(system_clock::now());
#ifdef _WIN32_WINNT
	localtime_s(&time, &now);
#else
	localtime_s(&now, &time);
#endif
}
