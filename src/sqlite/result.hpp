#ifndef _SQLITE_RESULT_H
#define _SQLITE_RESULT_H

#include <sqlite3.h>
#include <string_view>

class SQLiteResult
{
public:
	SQLiteResult(sqlite3 *db, const std::string_view &query);
	~SQLiteResult();
	const char* GetErrorMsg() const;
	int GetResultCode() const;
	std::string_view& GetQuery();
private:
	std::string_view m_query;
	char *m_error;
	int m_result;
};

#endif // _SQLITE_RESULT_H