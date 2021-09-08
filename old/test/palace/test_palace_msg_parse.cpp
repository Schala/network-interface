#include <iostream>
#include <string>

#include "palace/lib/codec.hpp"
#include "palace/lib/message.hpp"
#include "palace/lib/protocol.hpp"

int main(int argc, char **argv)
{
	std::cout << "Running Palace message parsing test... ";

	if (argc != 2)
	{
		std::cout << "no argument specified!" << std::endl;
		return -1;
	}

	PalaceCodec codec;
	std::string s(argv[1]);
	codec.Encode(s);

	PalaceMessage msg(MSGID_NOOP, 666);
	msg.PutCStr(s);

	return 0;
}
