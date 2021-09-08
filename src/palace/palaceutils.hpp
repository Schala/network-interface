#ifndef _PALACEUTILS_H
#define _PALACEUTILS_H

#include <array>
#include <cstdint>
#include <string>

typedef std::array<uint32_t, 512> _LookupTable;

constexpr _LookupTable _GenerateLUT()
{
	uint32_t key = 666666;
	uint32_t quo, rem, test;
	_LookupTable lut;

	for (auto &i : lut)
	{
		quo = key / 127773;
		rem = key % 127773;
		test = 16807 * rem - 2836 * quo;
		key = test > 0 ? test : test + 2147483647;
		i = static_cast<uint32_t>(static_cast<double>(key) / 2147483647.0 * 256.0);
	}

	return lut;
}

const _LookupTable _LUT = _GenerateLUT();

void Encode(std::string &data)
{
	uint8_t last = 0;
	uint32_t rc = 0;
	uint8_t b;

	if (data.size() > 254) data.resize(254);

	for (auto &i : data)
	{
		b = i;
		i = static_cast<uint8_t>(b ^ _LUT[rc++] ^ last);
		last = static_cast<uint8_t>(i ^ _LUT[rc++]);
	}
}

void Decode(std::string &data)
{
	uint8_t last = 0;
	uint32_t rc = 0;
	uint8_t b;

	for (auto &i : data)
	{
		b = i;
		i = static_cast<uint8_t>(b ^ _LUT[rc++] ^ last);
		last = static_cast<uint8_t>(b ^ _LUT[rc++]);
	}
}

#endif // _PALACEUTILS_H
