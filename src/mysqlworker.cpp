#include <utility>

#include "mysqlworker.hpp"

MySQLRec::MySQLRec()
{
}

MySQLRec::MySQLRec(MYSQL *db, const std::string_view &operation):
	op(std::move(operation)),
	result(mysql_query(db, operation.data()))
{
}

MySQLWorker::MySQLWorker(const std::string_view &host, const std::string_view &username,
	const std::string_view &password, uint16_t port, unsigned flags)
{
	m_db = mysql_init(nullptr);
	m_db = mysql_real_connect(m_db, host.data(), username.data(), password.data(), nullptr,
		port, nullptr, flags);
}

MySQLWorker::~MySQLWorker()
{
	Close();
}

void MySQLWorker::Close()
{
	std::scoped_lock lock(m_mutex);
	if (m_db) mysql_close(m_db);
}

int MySQLWorker::GetLastResult()
{
	std::scoped_lock lock(m_mutex);
	return m_current.result;
}

std::string_view MySQLWorker::GetLastError()
{
	std::scoped_lock lock(m_mutex);
	return std::string_view(m_current.error);
}

std::string_view MySQLWorker::GetLastOp()
{
	std::scoped_lock lock(m_mutex);
	return std::string_view(m_current.op);
}
