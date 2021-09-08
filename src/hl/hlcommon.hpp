#ifndef _HLCOMMON_H
#define _HLCOMMON_H

#include <array>
#include <cstdint>
#include <vector>

typedef std::vector<uint8_t> ByteString;
typedef std::array<uint8_t, 16> Bytes16;
typedef std::array<uint8_t, 20> Bytes20;

enum class HLMACAlgorithm : uint8_t
{
	None, MD5, SHA1, HMAC_MD5, HMAC_SHA1, HMAC_HAVAL
};

enum class HLCipher : uint8_t
{
	None, RC4, Blowfish, IDEA
};

enum class HLCompression : uint8_t
{
	None, GZip
};

#endif // _HLCOMMON_H
