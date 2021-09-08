#ifndef _KDXTHREADEDCODEC_H
#define _KDXTHREADEDCODEC_H

#include <mutex>

#include "kdxcodec.hpp"

class KDXThreadedCodec : public KDXCodec
{
public:
	uint32_t GetKey();
private:
	std::mutex m_mutex;
};

#endif // _KDXTHREADEDCODEC_H
