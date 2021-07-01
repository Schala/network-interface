#ifndef _LOG_COMMON_H
#define _LOG_COMMON_H

#include <cstdint>

enum class LogLevel : uint8_t
{
	None, Fatal, Error, Warning, Verbose, Debug
};

#endif // _LOG_COMMON_H