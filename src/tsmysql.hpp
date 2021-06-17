#ifndef _TSMYSQL_H
#define _TSMYSQL_H

#include <cstdint>
#include <string_view>

#include "tsdatabase.hpp"

struct MYSQL;

struct MySQLRec
{
	MySQLRec(MYSQL *db, const std::string_view &operation);

	std::string_view op;
	std::string_view error;
	int result;
};

class TSMySQL : public TSDatabase<MYSQL *, MySQLRec>
{
public:
	TSMySQL(const std::string_view &host, const std::string_view &username,
		const std::string_view password, uint16_t port = 0, unsigned flags = 0);
	~TSMySQL();
	void Close();
	int GetLastResult() const;
	std::string_view& GetLastError() const;
	std::string_view& GetLastOp() const;
	void Run();
};

#endif // _TSMYSQL_H
