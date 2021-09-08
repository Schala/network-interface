#include <algorithm>
#include <array>
#include <boost/predef.h>
#include <cstdio>
#include <iostream>

#define BUILD_CLIENT

#include "test_connection.hpp"
#include "../src/client.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
		std::cout << "Usage: test_client <address> <port>" << std::endl;
	
	Client<std::string, TestConnection> client;

	try
	{
		client.Connect(argv[1], static_cast<uint16_t>(std::stoul(argv[2])));
	}
	catch(...)
	{
		std::cerr << "Failed to connect to " << argv[1] << " on port " << argv[2] << std::endl;
		return 1;
	}

	bool quit = false;

	std::thread cliThread([&]()
	{
		while (!quit)
		{
			std::fflush(stdout);

			std::array<char, 1024> input;
			input.fill(0);

			if (std::fgets(input.data(), 1024, stdin) != nullptr)
			{
				// strip line endings
				std::replace_if(input.begin(), input.end(), [](char c)
				{
					return c == '\n' || c == '\r';
				}, 0);

				client.Send(std::string(input.data()));
			}
		}
	});

	while (!quit)
	{
		if (client.IsConnected())
		{
			if (!client.IsQueueEmpty())
			{
				auto m = client.GetNextMsg();
				std::cout << m.data << std::endl;
			}
		}
		else
		{
			quit = true;
		}
	}

	if (cliThread.joinable()) cliThread.join();
	return 0;
}
