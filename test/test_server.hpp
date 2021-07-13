#ifndef _TEST_SERVER_H
#define _TEST_SERVER_H

#include <string>
#include <utility>

#define BUILD_SERVER

#include "../src/server.hpp"

class TestServer : public ServerInterface<std::string>
{
public:
	TestServer(uint16_t port): ServerInterface<std::string>(port, 250, 10)
	{
	}
private:
	uint32_t m_nextID;

	bool OnClientConnect(std::shared_ptr<Connection<std::string>> client)
	{
		return true;
	}

	void OnClientDisconnect(std::shared_ptr<Connection<std::string>> client)
	{
	}

	void OnReceive(std::shared_ptr<Connection<std::string>> client, std::string &msg)
	{
		S_LOG.WriteMsg(CATEGORY, LogLevel::Verbose, std::move(msg));
	}
};

#endif // _SERVER_H
