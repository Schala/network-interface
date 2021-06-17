#include "server.hpp"

KDXServer::KDXServer(uint16_t port, size_t maxThreads, size_t maxFileTransfers):
	ServerInterface<>(port, maxThreads),
	m_fileTransferPool(maxFileTransfers)
{
	for (uint32_t &i : m_keys)
		i = m_codec.GetKey();
}
