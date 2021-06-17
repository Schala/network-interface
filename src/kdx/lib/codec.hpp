#ifndef _KDX_CODEC_H
#define _KDX_CODEC_H

#include <array>
#include <cstdint>
#include <vector>

uint32_t KDXGetSeed();

class KDXCodec
{
public:
	virtual uint32_t GetKey();
private:
	uint32_t SeedInputVector(uint32_t seed, size_t length);
private:
	std::vector<uint8_t> m_ivec;
	uint32_t m_seed;
	uint8_t m_arbitraryIndex;
};

uint32_t KDXEncrypt(uint32_t key, std::vector<uint8_t> &data);
uint32_t KDXDecrypt(std::vector<uint8_t> &data);

#endif // _KDX_CODEC_H
