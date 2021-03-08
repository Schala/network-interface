#include <iostream>
#include <string>
#include "palace_message.hpp"

int main(int argc, char **argv)
{
	cmm::str31 n(std::string("lol"));
	std::cout << (int)n.size << ' ' << n.chars << std::endl;

	return 0;
}