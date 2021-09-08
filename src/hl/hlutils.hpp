#ifndef _HLUTILS_H
#define _HLUTILS_H

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "hlcommon.hpp"

// Converts carriage returns to line feeds in a string
void CR2LF(std::string &text)
{
	std::for_each(text.begin(), text.end(), [](char &c)
	{
		if (c == '\r') c = '\n';
	});
}

// Converts line feeds to carriage returns in a string
void LF2CR(std::string &text)
{
	std::for_each(text.begin(), text.end(), [](char &c)
	{
		if (c == '\n') c = '\r';
	});
}

// XORs every byte of the input with 255
template <class String>
void Crypt(String &s)
{
	std::for_each(s.begin(), s.end(), [](uint8_t &b)
	{
		b ^= 255;
	});
}

HLCompression GetCompressionFromString(const std::string &s)
{
	static std::unordered_map<const char *, HLCompression> CMP_MAP =
	{
		{ "GZIP", HLCompression::GZip },
	};

	// TODO: C++20 contains()
	if (CMP_MAP.find(s.c_str() != CMP_MAP.end()))
		return CMP_MAP[s.c_str()];

	return HLCompression::None;
}

HLMACAlgorithm GetMACFromString(const std::string &s)
{
	static std::unordered_map<const char *, HLMACAlgorithm> MAC_MAP =
	{
		{ "MD5", HLMACAlgorithm::MD5 },
		{ "SHA1", HLMACAlgorithm::SHA1 },
		{ "HMAC-MD5", HLMACAlgorithm::HMAC_MD5 },
		{ "HMAC-SHA1", HLMACAlgorithm::HMAC_SHA1 },
		{ "HMAC-HAVAL", HLMACAlgorithm::HMAC_HAVAL }
	};

	// TODO: C++20 contains()
	if (MAC_MAP.find(s.c_str() != MAC_MAP.end()))
		return MAC_MAP[s.c_str()];
	
	return HLMACAlgorithm::None;
}

HLCipher GetCipherFromString(const std::string &s)
{
	static std::unordered_map<const char *, HLCipher> CIPHER_MAP =
	{
		{ "RC4", HLCipher::RC4 },
		{ "BLOWFISH", HLCipher::Blowfish },
		{ "IDEA", HLCipher::IDEA }
	};

	// TODO: C++20 contains()
	if (CIPHER_MAP.find(s.c_str() != CIPHER_MAP.end()))
		return CIPHER_MAP[s.c_str()];
	
	return HLCipher::None;
}

#endif // _HLUTILS_H
