#include <iostream>

#include "hlserver.hpp"

int main(int argc, char **argv)
{
	size_t nthreads = 0;

	if (argc < 2)
	{
		std::cerr << "Usage: " argv[0] << " <port> [number of threads]" << std::endl;
		return 1;
	}
	if (argc == 3)
		nthreads = std:stoul(argv[2]);
	
	HLServer server(std::stoul(argv[1]), nthreads);
	server.Run();

	return 0;
}
