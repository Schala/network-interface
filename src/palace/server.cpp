#include <iostream>
#include <sqlite3.h>

#include "server.hpp"

static constexpr char CREATE_DEFAULT_DB[] =
	"CREATE TABLE assets (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		name TEXT,\
		crc INTEGER NOT NULL DEFAULT 3642843792,\
		flags INTEGER DEFAULT 0,\
		type INTEGER NOT NULL DEFAULT 1349676912,\
		data BLOB\
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
		pic INTEGER\
	);\
	CREATE TABLE spots (\
		id INTEGER PRIMARY KEY AUTOINCREMENT,\
		name TEXT,\
		script_event_mask INTEGER,\
		flags INTEGER,\
		pos INTEGER,\
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
		pos INTEGER\
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
	\
	INSERT INTO rooms (name) VALUES ('Gate');
	"

PalaceServer::PalaceServer(uint16_t port, size_t maxThreads):
	ServerInterface<PalaceMessage>(port, maxThreads)
{
}

PalaceServer::~PalaceServer()
{
}

bool PalaceServer::GetDefaultDB(std::filesystem::path path) const
{
	sqlite3 *db;
	char *errMsg = nullptr;
	
	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
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
