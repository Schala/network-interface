#ifndef _MYSQLWORKER_H
#define _MYSQLWORKER_H

#include <cstdint>
#include <mysql/mysql.h>
#include <string_view>

#include "dbworker.hpp"

struct MySQLRec
{
	MySQLRec();
	MySQLRec(MYSQL *db, const std::string_view &operation);

	std::string_view op;
	std::string_view error;
	int result;
};

class MySQLWorker : public DBWorker<MYSQL *, MySQLRec>
{
public:
	MySQLWorker(const std::string_view &host, const std::string_view &username,
		const std::string_view &password, uint16_t port = 0, unsigned flags = 0);
	~MySQLWorker();
	void Close();
	int GetLastResult();
	std::string_view GetLastError();
	std::string_view GetLastOp();
	void Run();
};

#endif // _MYSQLWORKER_H
