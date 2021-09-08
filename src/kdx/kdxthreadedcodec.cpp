#include "kdxthreadedcodec.hpp"

uint32_t KDXThreadedCodec::GetKey()
{
	std::scoped_lock lock(m_mutex);
	return KDXCodec::GetKey();
}
