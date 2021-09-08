#ifndef _TEST_SERVER_H
#define _TEST_SERVER_H

#include <format>
#include <string>
#include <utility>

#define BUILD_SERVER

#include "../src/server.hpp"

class TestServer : public ServerBase<std::string>
{
public:
	TestServer(uint16_t port): ServerBase<std::string>(port, 250),
		m_nextID(0)
	{
	}
private:
	uint32_t m_nextID;

	bool OnClientConnect(std::shared_ptr<Connection<std::string>> client) override
	{
		S_LOG.WriteMsg(Connection<std::string>::CATEGORY, LogLevel::Verbose,
			std::format("Connection accepted from {}", client->GetAddressStr()));
		return true;
	}

	void OnClientDisconnect(std::shared_ptr<Connection<std::string>> client) override
	{
		S_LOG.WriteMsg(Connection<std::string>::CATEGORY, LogLevel::Verbose,
			std::format("Connection from {} has left the server.", client->GetAddressStr()));
	}

	void OnReceive(std::shared_ptr<Connection<std::string>> client, std::string &msg) override
	{
		SendAll(msg, client);
		S_LOG.WriteMsg(CATEGORY, LogLevel::Verbose,
			std::format("{}:\t{}", client->GetAddressStr(), msg));
	}
};

#endif // _SERVER_H
