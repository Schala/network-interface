#ifndef _TEST_SERVER_H
#define _TEST_SERVER_H

#include <string>

#define BUILD_SERVER

#include "../src/server.hpp"

class TestServer : public ServerInterface<std::string>
{
public:
	TestServer(uint16_t port): ServerInterface<std::string>(port, 250, 10)
	{
	}
protected:
	virtual bool OnClientConnect(std::shared_ptr<Connection<std::string>> client)
	{
		return true;
	}

	virtual void OnClientDisconnect(std::shared_ptr<Connection<std::string>> client)
	{
	}

	virtual void OnReceive(std::shared_ptr<Connection<std::string>> client, std::string &msg)
	{
		std::cout << msg << std::endl;
	}
};

#endif // _SERVER_H
