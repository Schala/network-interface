#ifndef _KDX_SERVER_H
#define _KDX_SERVER_H

#ifdef BUILD_SERVER

#include <array>

#include "../server.hpp"

class TSKDXCodec;

class KDXServer : public ServerInterface<>
{
public:
	KDXServer(uint16_t port, size_t maxThreads, size_t maxFileTransfers);
private:
	TSKDXCodec m_codec;
	std::array<uint32_t, 3> m_keys;
	boost::asio::thread_pool m_fileTransferPool;
};

#endif // BUILD_SERVER

#endif // _KDX_SERVER_H
