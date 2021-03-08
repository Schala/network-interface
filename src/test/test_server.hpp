#ifndef _TEST_SERVER_H
#define _TEST_SERVER_H

#include <string>

#include "../server.hpp"

class test_server : public cmm::server_interface<std::string>
{
public:
	test_server(cmm::uint16 port): cmm::server_interface<std::string>(port)
	{
	}
protected:
	virtual bool on_client_connect(std::shared_ptr<cmm::connection<std::string>> client)
	{
		return true;
	}

	virtual void on_client_disconnect(std::shared_ptr<cmm::connection<std::string>> client)
	{
	}

	virtual void on_receive(std::shared_ptr<cmm::connection<std::string>> client, std::string &msg)
	{
		std::cout << msg << std::endl;
	}
};

#endif // _SERVER_H
