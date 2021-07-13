#ifndef _SERVER_H
#define _SERVER_H

#ifdef BUILD_SERVER

#include <algorithm>
#include <format>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <thread>

#include "connection.hpp"
#include "logging/log.hpp"

template <class T> class ServerInterface
{
public:
	static const std::string_view CATEGORY;

	ServerInterface(uint16_t port, size_t capacity, size_t maxThreads);
	virtual ~ServerInterface();
	bool Start();
	void Stop();
	void Wait();
	void Send(std::shared_ptr<Connection<T>> client, const T &msg);
	void SendAll(const T &msg, std::shared_ptr<Connection<T>> ignore = nullptr);
	void Update(size_t maxMsgs = -1);
protected:
	TSQueue<OwnedMsg<T>> m_pendingIn;
	std::deque<std::shared_ptr<Connection<T>>> m_connections;
	boost::asio::io_context m_ctx;
	std::thread m_ctxThread;
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::thread_pool m_threadPool;
	size_t m_capacity;

	virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client);
	virtual void OnClientDisconnect(std::shared_ptr<Connection<T>> client);
	virtual void OnReceive(std::shared_ptr<Connection<T>> client, T &msg);
};

template <class T>
const std::string_view ServerInterface<T>::CATEGORY = "[SERVER]";

template <class T>
ServerInterface<T>::ServerInterface(uint16_t port, size_t capacity, size_t maxThreads):
	m_acceptor(m_ctx, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	m_threadPool(maxThreads),
	m_capacity(capacity)
{
}

template <class T>
ServerInterface<T>::~ServerInterface()
{
	Stop();
}

template <class T>
bool ServerInterface<T>::Start()
{
	try
	{
		Wait(); // issue work BEFORE starting context, or it will exit immediately

		m_ctxThread = std::thread([this]()
		{
			m_ctx.run();
		});
	}
	catch (std::runtime_error &e)
	{
		S_LOG.WriteMsg(CATEGORY, LogLevel::Fatal, std::format("Failed to start: {}", e.what()));
		return false;
	}

	S_LOG.WriteMsg(CATEGORY, LogLevel::Verbose, "Server started");
	return true;
}

template <class T>
void ServerInterface<T>::Stop()
{
	m_ctx.stop();
	if (m_ctxThread.joinable()) m_ctxThread.join();
	S_LOG.WriteMsg(CATEGORY, LogLevel::Verbose, "Server stopped");
}

template <class T>
void ServerInterface<T>::Wait()
{
	m_acceptor.async_accept(
		[this](std::error_code ec, boost::asio::ip::tcp::socket socket)
		{
			if (ec)
				S_LOG.WriteMsg(Connection<T>::CATEGORY, LogLevel::Error,
					ec.message());
			else
			{
				S_LOG.WriteMsg(Connection<T>::CATEGORY, LogLevel::Verbose,
					std::format("Incoming from {}", socket.remote_endpoint().address().to_string()));
					
				auto conn =
					std::make_shared<Connection<T>>(Connection<T>::Owner::Server, m_ctx,
						std::move(socket), m_pendingIn);
				
				if (OnClientConnect(conn))
					m_connections.push_back(std::move(conn));
				else
					S_LOG.WriteMsg(Connection<T>::CATEGORY, LogLevel::Warning,
						std::format("Connection denied from {}", conn->GetAddressStr()));
			}

			Wait();
		});
}

template <class T>
void ServerInterface<T>::Send(std::shared_ptr<Connection<T>> client, const T &msg)
{
	if (client && client->IsConnected())
		client->Send(msg);
	else
	{
		OnClientDisconnect(client);
		client.reset();
		m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), client),
			m_connections.end());
	}
}

template <class T>
void ServerInterface<T>::SendAll(const T &msg, std::shared_ptr<Connection<T>> ignore)
{
	bool invalidClientFound = false;

	for (auto &client : m_connections)
	{
		if (client && client->IsConnected())
		{
			if (client != ignore)
				client->Send(msg);
		}
		else
		{
			OnClientDisconnect(client);
			client.reset();
			invalidClientFound = true;
		}
	}

	if (invalidClientFound)
		m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), nullptr));
}

template <class T>
void ServerInterface<T>::Update(size_t maxMsgs)
{
	size_t msgCount = 0;

	while (msgCount++ < maxMsgs && !m_pendingIn.IsEmpty())
	{
		auto msg = m_pendingIn.PopFront();
		OnReceive(msg.remote, msg.data);
	}
}

template <class T>
bool ServerInterface<T>::OnClientConnect(std::shared_ptr<Connection<T>> client)
{
	return false;
}

template <class T>
void ServerInterface<T>::OnClientDisconnect(std::shared_ptr<Connection<T>> client)
{
}

template <class T>
void ServerInterface<T>::OnReceive(std::shared_ptr<Connection<T>> client, T &msg)
{
}

#endif // BUILD_SERVER

#endif // _SERVER_H
