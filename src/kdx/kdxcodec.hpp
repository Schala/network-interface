#ifndef _KDXCODEC_H
#define _KDXCODEC_H

#include <cstdint>
#include <vector>

uint32_t KDXGetSeed();

class KDXCodec
{
public:
	virtual uint32_t GetKey();
private:
private:
	std::vector<uint8_t> m_ivec;
	uint32_t m_seed;
	uint8_t m_arbitraryIndex;

	uint32_t SeedInitVector(uint32_t seed, size_t length);
};

uint32_t KDXEncrypt(uint32_t key, std::vector<uint8_t> &data);
uint32_t KDXDecrypt(std::vector<uint8_t> &data);

#endif // _KDXCODEC_H
