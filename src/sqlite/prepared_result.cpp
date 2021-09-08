#include <stdexcept>

#include "prepared_result.hpp"

SQLitePreparedResult::SQLitePreparedResult(sqlite3 *db, const std::string_view &query,
		const std::vector<SQLiteType> &columnTypes):
	m_query(query)
{
}

SQLitePreparedResult::~SQLitePreparedResult()
{
	sqlite3_free(m_error);
}

const char* SQLitePreparedResult::GetErrorMsg() const
{
	return m_error;
}

int SQLitePreparedResult::GetResultCode() const
{
	return m_result;
}

std::string_view& SQLitePreparedResult::GetQuery()
{
	return m_query;
}

SQLiteVariable SQLitePreparedResult::operator[](size_t index) const
{
	return m_vars.at(index);
}
