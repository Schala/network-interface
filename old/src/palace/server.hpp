#ifndef _PALACE_SERVER_H
#define _PALACE_SERVER_H

#include <atomic>
#include <filesystem>
#include <set>

#include "lib/protocol.hpp"
#include "../server.hpp"

class PalaceServer : public ServerBase<PalaceMessage>
{
public:
	PalaceServer(uint16_t port, size_t capacity, size_t maxThreads);
	~PalaceServer();
	constexpr uint8_t GetPlatform() const;
private:
	PalaceDBWorker m_dbWorker;
	std::thread m_dbWorkerThread;
	Str63 m_name;
	UL_CAPS m_ulCaps;
	DL_CAPS m_dlCaps;
	SERVER_PERMS m_perms;
	SERVER_OPTIONS m_options;
	std::atomic_uint32_t m_lastUserID;
	std::atomic_uint32_t m_lastAssetID;
	std::atomic_uint32_t m_lastBanID;
	std::atomic_uint32_t m_lastPasswordID;
	std::atomic_uint16_t m_lastRoomID;
	std::atomic_uint16_t m_lastSpotID;
	std::atomic_uint16_t m_lastStateID;
	std::atomic_uint16_t m_lastDrawID;
	std::atomic_uint16_t m_lastPointID;
	std::atomic_uint16_t m_lastLPropID;
	EXT_INFO_FLAGS_FLAGS m_flags;

	bool CreateDefaultDB(std::filesystem::path path) const;
	bool PurgeUnusedIDs();
	bool PurgeUnusedAssets();
};

#endif // _PALACE_SERVER_H
