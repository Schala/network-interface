#ifndef _KDX_CODEC_H
#define _KDX_CODEC_H

#include <boost/endian/conversion.hpp>

#include "../common.hpp"

namespace cmm
{
	template <class String> uint32 kdx_crypt(uint32 key, String &data)
	{
		uint32 len_ = data.size() >> 2;
		uint32 *ptr32_ = reinterpret_cast<uint32 *>(&data[0]);

		for (int i = 0; i < len_; i++)
		{
			key = (key << 1) + 0x4878;
			ptr32_[i] ^= boost::endian::big_to_native(key);
		}

		return key;
	}
}

#endif // _KDX_CODEC_H
