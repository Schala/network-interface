#ifndef _SERVER_H
#define _SERVER_H

#include <chrono>
#include <system_error>
#include <thread>
#include <vector>

#include "netqueue.hpp"
#include "packet.hpp"

// Base class for servers.
template <class Msg, class Protocol>
class ServerBase
{
public:
	typedef Packet<Msg, Protocol> PacketType;

	ServerBase() = delete;
	virtual ~ServerBase();

	// Runs the I/O context utilising the internal thread pool
	virtual void Run();

	// Stops the I/O context on all threads
	void Stop();
protected:
	boost::asio::io_context m_ctx;
	std::chrono::seconds m_timeout;
	NetQueue<PacketType> m_in;
	size_t m_capacity;

	// Should only be instantiated by deriving class constructors
	ServerBase(size_t numThreads = 0);

	// Called before I/O stops
	virtual void OnStop();
private:
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workGuard;
	std::vector<std::thread> m_threadPool;
	size_t m_numThreads;
};

template <class Msg, class Protocol>
ServerBase<Msg, Protocol>::ServerBase(size_t numThreads):
	m_workGuard(m_ctx.get_executor())
{
	// Assume 0 means approx. CPU limit
	if (numThreads == 0) numThreads = std::thread::hardware_concurrency();
	m_ctx = boost::asio::io_context(numThreads);
	m_numThreads = numThreads;
}

template <class Msg, class Protocol>
ServerBase<Msg, Protocol>::~ServerBase()
{
	Stop();
}

template <class Msg, class Protocol>
void ServerBase<Msg, Protocol>::Run()
{
	for (size_t i = 0; i < m_numThreads; i++)
		m_threadPool.emplace_back(std::thread([this]
		{
			m_ctx.run();
		}));
}

template <class Msg, class Protocol>
void ServerBase<Msg, Protocol>::Stop()
{
	OnStop();
	m_ctx.stop();
}

template <class Msg, class Protocol>
void ServerBase<Msg, Protocol>::OnStop()
{
}

#endif // _SERVER_H
