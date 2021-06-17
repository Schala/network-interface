#ifndef _TSSQLITE_H
#define _TSSQLITE_H

#include <filesystem>
#include <string_view>
#include <vector>

#include "tsdatabase.hpp"

struct sqlite3;
struct sqlite3_stmt;

enum class SQLiteOpType : uint8_t
{
	Read, Write
};

struct SQLiteRec
{
	SQLiteRec(const std::string_view &operation, SQLiteOpType kind);
	~SQLiteRec();

	std::string_view op;
	char *error;
	sqlite3_stmt *compiled;
	int result;
	SQLiteOpType kind;
};

class TSSQLite : public TSDatabase<sqlite3 *, SQLiteRec>
{
public:
	TSSQLite(const std::filesystem::path &dbPath);
	~TSSQLite();
	void Close();
	int GetLastResult() const;
	std::string_view& GetLastError() const;
	std::string_view& GetLastOp() const;
	void Run();
};

#endif // _TSSQLITE_H
