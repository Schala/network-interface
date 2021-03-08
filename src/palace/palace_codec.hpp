#ifndef _PALACE_CODEC_H
#define _PALACE_CODEC_H

#include <array>

#include "../common.hpp"

namespace cmm
{
	class codec
	{
	public:
		codec()
		{
			uint32 key_ = 666666;
			uint32 quo_, rem_, test_;

			for (auto &i : lut_)
			{
				quo_ = key_ / 127773;
				rem_ = key_ % 127773;
				test_ = 16807 * rem_ - 2836 * quo_;
				key_ = test_ > 0 ? test_ : test_ + 2147483647;
				i = static_cast<uint32>(static_cast<double>(key_) / 2147483647.0 * 256.0);
			}
		}

		template <class String> void encode(String &data)
		{
			uint8 last_ = 0;
			uint32 rc_ = 0;
			uint8 b_;

			if (data.size() > 254) data.resize(254);

			for (auto &i : data)
			{
				b_ = i;
				i = static_cast<uint8>(b_ ^ lut_[rc_++] ^ last_);
				last_ = static_cast<uint8>(i ^ lut_[rc_++]);
			}
		}

		template <class String> void decode(String &data)
		{
			uint8 last_ = 0;
			uint32 rc_ = 0;
			uint8 b_;

			for (auto &i : data)
			{
				b_ = i;
				i = static_cast<uint8>(b_ ^ lut_[rc_++] ^ last_);
				last_ = static_cast<uint8>(b_ ^ lut_[rc_++]);
			}
		}
	private:
		std::array<uint32, 512> lut_;
	};
}

#endif // _PALACE_CODEC_H
