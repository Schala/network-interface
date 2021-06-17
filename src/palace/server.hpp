#ifndef _PALACE_SERVER_H
#define _PALACE_SERVER_H

#include <filesystem>
#include <string>

#include "../server.hpp"

class PalaceMessage;
class TSSQLite;
struct UL_CAPS;
struct DL_CAPS;

class PalaceServer : public ServerInterface<PalaceMessage>
{
public:
	PalaceServer(uint16_t port, size_t maxThreads);
	~PalaceServer();
private:
	TSSQLite m_db;
	std::thread m_dbThread;
	UL_CAPS m_ulCaps;
	DL_CAPS m_dlCaps;

	bool GetDefaultDB(std::filesystem::path path) const;
};

#endif // _PALACE_SERVER_H
