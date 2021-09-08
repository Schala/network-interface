#include "codec.hpp"

PalaceCodec::PalaceCodec()
{
	uint32_t key = 666666;
	uint32_t quo, rem, test;

	for (auto &i : m_lut)
	{
		quo = key / 127773;
		rem = key % 127773;
		test = 16807 * rem - 2836 * quo;
		key = test > 0 ? test : test + 2147483647;
		i = static_cast<uint32_t>(static_cast<double>(key) / 2147483647.0 * 256.0);
	}
}

template <class String> void PalaceCodec::Encode(String &data)
{
	uint8_t last = 0;
	uint32_t rc = 0;
	uint8_t b;

	if (data.size() > 254) data.resize(254);

	for (auto &i : data)
	{
		b = i;
		i = static_cast<uint8_t>(b ^ m_lut[rc++] ^ last);
		last = static_cast<uint8_t>(i ^ m_lut[rc++]);
	}
}

template <class String> void PalaceCodec::Decode(String &data)
{
	uint8_t last = 0;
	uint32_t rc = 0;
	uint8_t b;

	for (auto &i : data)
	{
		b = i;
		i = static_cast<uint8_t>(b ^ m_lut[rc++] ^ last);
		last = static_cast<uint8_t>(b ^ m_lut[rc++]);
	}
}
