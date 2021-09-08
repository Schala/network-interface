#ifndef _PALACE_CODEC_H
#define _PALACE_CODEC_H

#include <array>
#include <cstdint>

class PalaceCodec
{
public:
	PalaceCodec();
	template <class String> void Encode(String &data);
	template <class String> void Decode(String &data);
private:
	std::array<uint32_t, 512> m_lut;
};

#endif // _PALACE_CODEC_H
