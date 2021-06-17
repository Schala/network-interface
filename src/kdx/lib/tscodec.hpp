#ifndef _KDX_TS_CODEC_H
#define _KDX_TS_CODEC_H

#include <mutex>

#include "codec.hpp"

class TSKDXCodec : public KDXCodec
{
public:
	uint32_t GetKey();
private:
	std::mutex m_mutex;
};

#endif // _KDX_TS_CODEC_H
