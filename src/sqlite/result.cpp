#include <stdexcept>

#include "result.hpp"

SQLiteResult::SQLiteResult(sqlite3 *db, const std::string_view &query):
	m_query(query)
{
	try
	{
		m_result = sqlite3_exec(db, query.data(), nullptr, nullptr, &m_error);
	}
	catch (std::runtime_error &e)
	{
	}
}

SQLiteResult::~SQLiteResult()
{
	sqlite3_free(m_error);
}

const char* SQLiteResult::GetErrorMsg() const
{
	return m_error;
}

int SQLiteResult::GetResultCode() const
{
	return m_result;
}

std::string_view& SQLiteResult::GetQuery() const
{
	return m_query;
}
