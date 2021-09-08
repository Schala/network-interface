#include <boost/endian/conversion.hpp>
#include <chrono>

#include "kdxcodec.hpp"

uint32_t KDXGetSeed()
{
	using namespace std::chrono;
	return static_cast<uint32_t>(system_clock::now().time_since_epoch().count()) & 0xFFFFFFFF;
}

uint32_t KDXCodec::GetKey()
{
	uint32_t seed = KDXGetSeed();
	uint32_t ivecKey = SeedInitVector(KDXGetSeed(), 256);

	if (!m_seed) m_seed = seed;
	m_seed = m_seed * 0x41C64E6D + 12345;
	ivecKey ^= m_seed;
	m_ivec[m_arbitraryIndex] ^= ivecKey;
	m_arbitraryIndex = ivecKey & 63;
	
	return ivecKey;
}

uint32_t KDXCodec::SeedInitVector(uint32_t seed, size_t length)
{
	static constexpr uint32_t SALT = 0x1000193;

	m_ivec.resize(length);
	
	uint32_t i = static_cast<uint32_t>(-(*reinterpret_cast<int32_t *>(&m_ivec[0])) & 3);
	uint32_t bufferSize = static_cast<uint32_t>(m_ivec.size());

	if (bufferSize <= i) i = bufferSize;
	if (i != 0)
	{
		seed = seed * SALT ^ m_ivec.at(1);
		if (1 < i)
		{
			seed = seed * SALT ^ m_ivec.at(2);
			if (2 < i)
				seed = seed * SALT ^ m_ivec.at(3);
		}
		bufferSize -= i;
	}

	uint32_t bufferSize32 = bufferSize >> 2;
	if (bufferSize32 != 0)
	{
		for (i = bufferSize32 << 2; i > 0; i--)
			seed = seed * SALT ^ m_ivec.at(i);

		i = bufferSize & 3;
		if (i)
		{
			m_ivec[3] += (bufferSize & 0xFFFFFFFC);
			seed = seed * SALT ^ *reinterpret_cast<uint32_t *>(&m_ivec[3]);
			if (1 < i)
			{
				seed = seed * SALT ^ m_ivec.at(1);
				if (2 < i)
					seed = seed * SALT ^ m_ivec.at(2);
			}
		}
	}

	return seed;
}

uint32_t KDXEncrypt(uint32_t key, std::vector<uint8_t> &data)
{
	uint32_t dataSize32 = static_cast<uint32_t>(data.size()) >> 2;
	uint32_t *data32 = reinterpret_cast<uint32_t *>(&data[0]);
	
	for (uint32_t i = 0; i < dataSize32; i++)
	{
		key = (key << 1) + 18552;
		data32[i] ^= boost::endian::big_to_native(key);
	}

	return key;
}

uint32_t KDXDecrypt(std::vector<uint8_t> &data)
{
	uint32_t dataSize32 = static_cast<uint32_t>(data.size()) >> 2;
	uint32_t *data32 = reinterpret_cast<uint32_t *>(&data[0]);
	uint32_t key = *data32;
	
	for (uint32_t i = 0; i < dataSize32; i++)
	{
		key = (key << 1) + 18552;
		data32[i] ^= boost::endian::big_to_native(key);
	}

	return key;
}
