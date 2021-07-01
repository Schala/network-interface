#include "test_server.hpp"

int main(int argc, char **argv)
{
	TestServer srv(6666);
	srv.Start();

	while (1)
		srv.Update();
		
	return 0;
}
