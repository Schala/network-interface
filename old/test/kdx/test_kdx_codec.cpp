#include <cstring>
#include <iomanip>
#include <iostream>

#include "kdx/lib/codec.hpp"

int main(int argc, char **argv)
{
	std::cout << "Running KDX codec test... ";

	if (argc != 2)
	{
		std::cout << "no argument specified!" << std::endl;
		return -1;
	}

	KDXCodec codec;
	uint32_t key = codec.GetKey();
	size_t datalen = std::strlen(argv[1]);
	std::vector<uint8_t> data(datalen, 0);

	std::memcpy(&data[0], argv[1], datalen);

	std::vector<uint8_t> encData(data);
	uint32_t encKey = KDXEncrypt(key, encData);
	std::vector<uint8_t> decData(encData);
	uint32_t decKey = KDXDecrypt(decData);

	for (int i = 0; i < decData.size(); i++)
		if (data[i] != decData[i])
		{
			std::cout << "FAILED: mismatch between original and re-decrypted data!" << std::endl << std::endl;

			std::cout << "Expected:";
			for (int b : data) std::cout << ' ' << std::hex << std::setw(2) << std::setfill('0') << b;
			std::cout << std::endl;

			std::cout << "Received:";
			for (int b : decData) std::cout << ' ' << std::hex << std::setw(2) << std::setfill('0') << b;
			std::cout << std::endl;

			return -2;
		}

	std::cout << "SUCCESS!" << std::endl;
	return 0;
}
