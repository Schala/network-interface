#ifndef _HLSERVER_H
#define _HLSERVER_H

#include <atomic>
#include <map>
#include <set>
#include <string_view>

#include "../server.hpp"
//#include "hlservertrackersession.hpp"
#include "hlsession.hpp"

class HLServer : public ServerBase<HLTransaction, boost::asio::ip::tcp>
{
public:
	static const uint16_t Version = 197;
	
	HLServer(uint16_t port, size_t numThreads = 0);
	~HLServer();

	// Spawns the listening operation and initiates I/O threads
	void Run();
private:
	boost::asio::ip::tcp::acceptor m_acceptor;
	std::string m_name;
	std::string m_flatNews;
	std::string m_agreement;
	std::map<uint16_t, HLSessionPtr> m_clientSessions;
	//HLServerTrackerSessionSet m_trackerSessions;
	HLAccountSet m_accounts;
	std::atomic_uint16_t m_lastIssuedID;

	// Calls the session's Send() with the specified transaction
	void Send(HLSessionPtr user, const HLTransaction &trans);

	// Sends a transaction to all users
	void SendAll(HLTransaction &trans, const HLSessionPtr &ignore = nullptr);

	// Purge invalid/disconnected sessions
	void PurgeGhosts();

	boost::asio::awaitable<void> Listen();
	boost::asio::awaitable<void> ProcessQueue();
	void OnStop() override;

	void HandleLogin(const PacketType &p);

	// Called by HandleLogin() to send a reply back to the user
	// Version < 151: sends version + SetClientUserInfo with only name and icon, no reply expected
	// Version >= 151: sends version + banner ID (0), server name
	// Also sends NoAgreement or Agreement afterwards as well as UserAccess
	void SendLoginReply(HLSessionPtr user);

	// Called if there was a problem with the packet
	void HandleError(HLSessionPtr user, const std::string_view &message);

	// Blank reply
	void HandleAgreed(const PacketType &p);

	// Used internally by HandleAgreed() for a default message
	void HandleAgreedDefault(const PacketType &p);

	// Replies with array of HLUserInfos
	void HandleGetUserNameList(const PacketType &p);

	// Send a generic reply
	void SendReply(HLSessionPtr user);

	// Sends the user's access bitmap
	void SendUserAccess(HLSessionPtr user);
};

#endif // _HLSERVER_H
