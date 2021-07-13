#ifndef _LOG_APPENDER_H
#define _LOG_APPENDER_H

#include <string>
#include <string_view>

#include "message.hpp"

struct LogAppenderFlags
{
	uint8_t
		compress : 1, // file only
		colour : 1; // console only
};

struct LogMsg;

class LogAppender
{
public:
	static constexpr std::string_view GetLevelStr(LogLevel level);

	LogAppender(const LogAppenderFlags &flags, LogLevel level);
	virtual ~LogAppender();
	virtual void Close();
	void Write(const LogMsg &msg);
	LogLevel GetLevel() const;
	void SetLevel(LogLevel level);
protected:
	LogAppenderFlags m_flags;
	LogLevel m_level;

	virtual void OnBeginFormat(std::string &text, const LogMsg &msg);
	virtual void OnWrite(const std::string &msg) = 0;
};

#endif // _LOG_APPENDER_H
