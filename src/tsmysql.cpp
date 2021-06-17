#include <mysql/mysql.h>
#include <utility>

#include "tsmysql.hpp"

MySQLRec::MySQLRec(MYSQL *db, const std::string_view &operation):
	op(std::move(operation)),
	result(mysql_query(db, operation.data()))
{
}

TSMySQL::TSMySQL(const std::string_view &host, const std::string_view &username,
	const std::string_view password, uint16_t port, unsigned flags):

{
	m_db = mysql_init(nullptr);
	m_db = mysql_real_connect(m_db, host.data(), username.data(), password.data(), nullptr,
		port, nullptr, flags);
}

TSMySQL::~TSMySQL()
{
	Close();
}

void TSMySQL::Close()
{
	std::scoped_lock lock(m_mutex);
	if (m_db) mysql_close(m_db);
}

int TSMySQL::GetLastResult() const
{
	std::scoped_lock lock(m_mutex);
	return m_current.result;
}

std::string_view& TSMySQL::GetLastError() const
{
	std::scoped_lock lock(m_mutex);
	return m_current.error;
}

std::string_view& TSMySQL::GetLastOp() const
{
	std::scoped_lock lock(m_mutex);
	return m_current.op;
}

void TSMySQL::Run()
{
}
