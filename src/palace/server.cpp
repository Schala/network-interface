#include <boost/predef.h>
#include <iostream>
#include <openssl/sha.h>
#include <sqlite3.h>

#include "lib/asset.hpp"
#include "lib/protocol.hpp"
#include "dbworker.hpp"
#include "server.hpp"

static constexpr char CREATE_DEFAULT_DB[] =
	"CREATE TABLE assets (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		name TEXT,\
		crc INTEGER NOT NULL DEFAULT 3642843792,\
		flags INTEGER DEFAULT 0,\
		type INTEGER NOT NULL DEFAULT 1349676912,\
	);\
	CREATE TABLE rooms (\
		id INTEGER PRIMARY KEY AUTOINCREMENT DEFAULT 86,\
		name TEXT NOT NULL DEFAULT 'New Room',\
		flags INTEGER DEFAULT 256,\
		faces INTEGER DEFAULT 0,\
		bg TEXT NOT NULL DEFAULT 'clouds.jpg',\
		artist TEXT,\
		password BLOB,\
		spots TEXT,\
		pics TEXT,\
		draws TEXT,\
		lprops TEXT\
	);\
	CREATE TABLE points (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		v INTEGER,\
		h INTEGER\
	);\
	CREATE TABLE pictures (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		path TEXT NOT NULL,\
		alpha INTEGER\
	);\
	CREATE TABLE states (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		pic INTEGER,\
		v INTEGER,\
		h INTEGER\
	);\
	CREATE TABLE spots (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		name TEXT,\
		script_event_mask INTEGER,\
		flags INTEGER,\
		v INTEGER,\
		h INTEGER,\
		dest INTEGER,\
		type INTEGER DEFAULT 0,\
		state INTEGER DEFAULT 0,\
		points TEXT,\
		states TEXT,\
		script TEXT\
	);\
	CREATE TABLE draws (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		cmd INTEGER DEFAULT 0,\
		data BLOB\
	);\
	CREATE TABLE lprops (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		asset INTEGER,\
		v INTEGER,\
		h INTEGER\
	);\
	CREATE TABLE bans (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		ip TEXT NOT NULL,\
		expires INTEGER,\
		info TEXT\
	);\
	CREATE TABLE passwords (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		hash TEXT NOT NULL,\
		password BLOB NOT NULL\
	);\
	CREATE TABLE clients (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		sig VARCHAR(6) NOT NULL,\
		name TEXT NOT NULL,\
	);\
	\
	INSERT INTO rooms (name) VALUES ('Gate');\
	\
	INSERT INTO clients (sig, name)\
	VALUES\
		('350211', 'ThePalace'),\
		('PC4237', 'PalaceChat'),\
		('OPNPAL', 'OpenPalace'),\
		('J2.0', 'InstantPalace');\
	"

struct BanRec
{
	std::string_view ip;
	uint64_t expires;
	std::string_view info;
};

struct PictureRec
{
	std::string_view path;
	uint16_t alpha;
};

struct PasswordRec
{
	std::array<uint8_t, SHA512_DIGEST_LENGTH> hash;
	Str31 data;
};

struct ClientRec
{
	std::array<char, 6> sig;
	std::string_view name;
}

PalaceServer::PalaceServer(uint16_t port, size_t capacity, size_t maxThreads):
	ServerInterface<PalaceMessage>(port, capacity, maxThreads)
{
}

PalaceServer::~PalaceServer()
{
}

constexpr uint8_t PalaceServer::GetPlatform() const
{
#if BOOST_OS_MACOS
	return PLAT_MAC;
#elif BOOST_OS_WINDOWS
	return PLAT_WINNT;
#else
	return PLAT_UNIX;
#endif
}

bool PalaceServer::CreateDefaultDB(std::filesystem::path path) const
{
	sqlite3 *db;
	char *errMsg = nullptr;
	
	if (sqlite3_open(path.string().data(), &db) != SQLITE_OK)
	{
		std::cerr << "Unable to write new database to " << path << ": " <<
			sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return false;
	}

	if (sqlite3_exec(db, CREATE_DEFAULT_DB, nullptr, nullptr, &errMsg) != SQLITE_OK)
	{
		std::cerr << "Unable to write new database to " << path << ": " <<
			errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return false;
	}

	sqlite3_close(db);
	return true;
}

bool PalaceServer::CleanUnusedIDs() const
{
	std::vector<Point> points;
	std::vector<Asset> assets;
	std::vector<BanRec> bans;
	std::vector<PictureRec> pics;
	std::vector<PasswordRec> passwords;
	std::vector<ClientRec> clients;
}
