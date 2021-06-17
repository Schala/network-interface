#include "tscodec.hpp"

uint32_t TSKDXCodec::GetKey()
{
	std::scoped_lock lock(m_mutex)
	return KDXCodec::GetKey();
}
