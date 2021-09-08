#ifndef _CLIENT_H
#define _CLIENT_H

#ifdef BUILD_CLIENT

#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <type_traits>
#include <utility>

#include "../src/connection.hpp"

/// Constraint to ensure a template parameter derives from the Connection template class. Incorporation pending
template <class Msg, class Derived>
concept ConnectionDerived = std::is_base_of<Connection<Msg>, Derived>::value;

template <class Msg, class Conn> class Client
{
public:
	virtual ~Client();
	void Connect(const std::string_view &host, uint16_t port);
	void Disconnect();
	bool IsConnected() const;
	void Send(Msg &&msg);
	OwnedMsg<Msg> GetNextMsg();
	bool IsQueueEmpty() const;
	virtual void Ping();
protected:
	boost::asio::io_context m_ctx;
	std::thread m_ctxThread;
	TSQueue<OwnedMsg<Msg>> m_incoming;
	std::unique_ptr<Conn> m_connection;
};

template <class Msg, class Conn>
Client<Msg, Conn>::~Client()
{
	Disconnect();
}

template <class Msg, class Conn>
void Client<Msg, Conn>::Connect(const std::string_view &host, uint16_t port)
{
	boost::asio::ip::tcp::resolver resolver(m_ctx);
	boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host,
		std::to_string(port));
	
	m_connection = std::make_unique<Conn>(Conn::Owner::Client, m_ctx,
		boost::asio::ip::tcp::socket(m_ctx), m_incoming);

	m_connection->ConnectToServer(std::move(endpoints));
	
	m_ctxThread = std::thread([this]()
	{
		m_ctx.run();
	});
}

template <class Msg, class Conn>
void Client<Msg, Conn>::Disconnect()
{
	if (IsConnected()) m_connection->Disconnect();
	m_ctx.stop();
	if (m_ctxThread.joinable()) m_ctxThread.join();
	m_connection.reset(nullptr);
}

template <class Msg, class Conn>
bool Client<Msg, Conn>::IsConnected() const
{
	if (m_connection)
		return m_connection->IsConnected();
	return false;
}

template <class Msg, class Conn>
void Client<Msg, Conn>::Send(Msg &&msg)
{
	if (IsConnected())
		m_connection->TakeAndSend(std::move(msg));
}

template <class Msg, class Conn>
OwnedMsg<Msg> Client<Msg, Conn>::GetNextMsg()
{
	return m_incoming.PopFront();
}

template <class Msg, class Conn>
bool Client<Msg, Conn>::IsQueueEmpty() const
{
	return m_incoming.IsEmpty();
}

template <class Msg, class Conn>
void Client<Msg, Conn>::Ping()
{
}

#endif // BUILD_CLIENT

#endif // _CLIENT_H
