#ifndef _LOG_APPENDER_H
#define _LOG_APPENDER_H

#include <string>

#include "common.hpp"

struct LogAppenderFlags
{
	unsigned
		compress : 1; // file only
};

struct LogMsg;

class LogAppender
{
public:
	static constexpr std::wstring_view GetLevelStr(LogLevel level);

	LogAppender(const LogAppenderFlags &flags, LogLevel level);
	virtual ~LogAppender();
	virtual void Close();
	void Write(const LogMsg &msg);
	LogLevel GetLevel() const;
	void SetLevel(LogLevel level);
protected:
	LogAppenderFlags m_flags;
	LogLevel m_level;

	virtual void OnWrite(const std::wstring &msg) = 0;
};

#endif // _LOG_APPENDER_H
