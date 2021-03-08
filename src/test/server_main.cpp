#include "test_server.hpp"

int main(int argc, char **argv)
{
	test_server srv(6666);
	srv.start();

	while (1)
		srv.update();
		
	return 0;
}
