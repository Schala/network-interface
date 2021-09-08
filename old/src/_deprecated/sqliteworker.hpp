#ifndef _TSSQLITE_H
#define _TSSQLITE_H

#include <filesystem>
#include <sqlite3.h>
#include <string_view>
#include <variant>
#include <vector>

#include "dbworker.hpp"

enum class SQLiteOpType : uint8_t
{
	Read, Write
};

struct SQLiteRec
{
	SQLiteRec();
	SQLiteRec(const std::string_view &operation, SQLiteOpType kind);
	~SQLiteRec();

	std::string_view op;
	std::string_view error;
	std::vector<std::variant<
		std::vector<uint8_t>,
		double,
		float,
		int8_t, uint8_t,
		int16_t, uint16_t,
		int32_t, uint32_t,
		int64_t, uint64_t,
		std::string, std::u16string>> payload;
	sqlite3_stmt *compiled;
	int result;
	SQLiteOpType kind;
};

class SQLiteWorker : public DBWorker<sqlite3 *, SQLiteRec>
{
public:
	SQLiteWorker(const std::filesystem::path &dbPath);
	~SQLiteWorker();
	void Close();
	int GetLastResult();
	std::string_view GetLastError();
	std::string_view GetLastOp();
};

#endif // _TSSQLITE_H
