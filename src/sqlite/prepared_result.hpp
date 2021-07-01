#ifndef _SQLITE_PREPARED_RESULT_H
#define _SQLITE_PREPARED_RESULT_H

#include <cstdint>
#include <optional>
#include <sqlite3.h>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

typedef std::variant<
			std::vector<uint8_t>, // blob
			double, // real
			float,
			int8_t, uint8_t, // integer
			int16_t, uint16_t,
			int32_t, uint32_t,
			int64_t, uint64_t,
			std::string, std::u16string /* text, varchar */> SQLiteVariable;

enum class SQLiteType : uint8_t
{
	Null,
	Blob, // blob
	String, Unicode, // text, varchar
	Float, Double, // real
	Int8, UInt8, // integer
	Int16, UInt16,
	Int32, UInt32,
	Int64, UInt64
};

class SQLitePreparedResult
{
public:
	SQLitePreparedResult(sqlite3 *db, const std::string_view &query,
		const std::vector<SQLiteType> &columnTypes);
	~SQLitePreparedResult();
	const char* GetErrorMsg() const;
	int GetResultCode() const;
	std::string_view& GetQuery() const;
	SQLiteVariable& operator[](size_t index) const;
private:
	std::vector<SQLiteVariable> m_vars;
	sqlite3_stmt *m_stmt;
	std::string_view m_query;
	char *m_error;
	int m_result;
};

#endif // _SQLITE_PREPARED_RESULT_H
