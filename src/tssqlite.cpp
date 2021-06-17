#include <future>
#include <iostream>
#include <sqlite3.h>
#include <utility>

#include "tssqlite.hpp"

SQLiteRec::SQLiteRec(const std::string_view &operation, SQLiteOpType kind):
	op(std::move(operation)),
	error(nullptr),
	compiled(nullptr),
	result(SQLITE_OK),
	kind(kind)
{
}

SQLite::~SQLiteRec()
{
	if (error) sqlite3_free(error);
}

TSSQLite::TSSQLite(const std::filesystem::path &dbPath)
{
	if (sqlite3_open(dbPath.c_str(), &m_db) != SQLITE_OK)
	{
		std::cerr << "Unable to access database at " << path << ": " <<
			sqlite3_errmsg(db) << std::endl;
		Close();
	}
}

TSSQLite::~TSSQLite()
{
	Close();
}

void TSSQLite::Close()
{
	std::scoped_lock lock(m_mutex);
	if (m_db) sqlite3_close(m_db);
}

int TSSQLite::GetLastResult() const
{
	std::scoped_lock lock(m_mutex);
	return m_current.result;
}

std::string_view& TSSQLite::GetLastError() const
{
	std::scoped_lock lock(m_mutex);
	return m_current.error;
}

std::string_view& TSSQLite::GetLastOp() const
{
	std::scoped_lock lock(m_mutex);
	return m_current.op;
}

void TSSQLite::Run()
{
	if (!m_db) return;

	std::future<void> doRun = std::async([this]()
	{
		std::scoped_lock lock(this->m_mutex);
		SQLiteRec rec = this->m_pending.PopFront();

		switch (rec.kind)
		{
			case SQLiteOpType::Read:
				break;
			case SQLiteOpType::Write:
				rec.result = sqlite3_exec(m_db, rec.op.data(), nullptr, nullptr, rec.error);
		}

		Run();
	});

	doRun.wait();
}
