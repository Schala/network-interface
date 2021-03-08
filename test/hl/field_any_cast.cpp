#include <iostream>

#include "../../src/hl/message.hpp"

int main()
{
	cmm::field f;

	f.header.id = cmm::param::user_name;
	f.data = std::string("Billy Bob");
	
	std::cout << f.size() << std::endl;

	return 0;
}
