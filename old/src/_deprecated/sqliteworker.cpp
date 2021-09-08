#include <iostream>
#include <utility>

#include "tssqlite.hpp"

SQLiteRec::SQLiteRec()
{
}

SQLiteRec::SQLiteRec(const std::string_view &operation, SQLiteOpType kind):
	op(std::move(operation)),
	error(nullptr),
	compiled(nullptr),
	result(SQLITE_OK),
	kind(kind)
{
}

SQLiteRec::~SQLiteRec()
{
	if (compiled) sqlite3_finalize(compiled);
}

SQLiteWorker::SQLiteWorker(const std::filesystem::path &dbPath)
{
	if (sqlite3_open(dbPath.string().data(), &m_db) != SQLITE_OK)
	{
		std::cerr << "Unable to access database at " << dbPath << ": " <<
			sqlite3_errmsg(m_db) << std::endl;
		Close();
	}
}

SQLiteWorker::~SQLiteWorker()
{
	Close();
}

void SQLiteWorker::Close()
{
	std::scoped_lock lock(m_mutex);
	if (m_db) sqlite3_close(m_db);
}

int SQLiteWorker::GetLastResult()
{
	std::scoped_lock lock(m_mutex);
	return m_current.result;
}

std::string_view SQLiteWorker::GetLastError()
{
	std::scoped_lock lock(m_mutex);
	return std::string_view(m_current.error);
}

std::string_view SQLiteWorker::GetLastOp()
{
	std::scoped_lock lock(m_mutex);
	return std::string_view(m_current.op);
}
