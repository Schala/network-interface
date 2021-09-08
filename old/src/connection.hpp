#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <memory>
#include <string_view>
#include <system_error>
#include <utility>

//#include "config.h"
#include "owned_msg.hpp"
#include "tsqueue.hpp"

/// A connection between a client and a server
template <class T> class Connection : public std::enable_shared_from_this<Connection<T>>
{
public:
	static const std::string_view CATEGORY;
	
	enum class Owner : uint8_t
	{
		Server, Client
	};

	Connection(Owner parent, boost::asio::io_context &context,
		boost::asio::ip::tcp::socket socket, TSQueue<OwnedMsg<T>> &inQueue);

	/// Client-side function for connecting to a server after host resolution
	boost::asio::awaitable<void> ConnectToServer(boost::asio::ip::tcp::resolver::results_type &&endpoints);

	/// Server-side function for priming a client connection after successful accept
	void ConnectToClient();

	void Disconnect();
	virtual ~Connection();
	bool IsConnected() const;

	/// Sends a message to the remote endpoint, but allows retention of the message
	virtual void Send(const T &msg);

	/// Sends a message to the remote endpoint, but invalidates further use of the message
	virtual void TakeAndSend(T &&msg);

	std::string GetAddressStr() const;

	/// Called once a connection has been accepted
	virtual void OnAccept();

	/// Called if an error occurs, providing said error for diagnosis and/or further action
	virtual void OnError(std::error_code &&ec);

	/// Called before disconnection
	virtual void OnDisconnect();

	/// Called when the remote endpoint pings the connection
	virtual void OnPing();

	void AddToQueue(T &&msg);

protected:
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::io_context &m_ctx;
	TSQueue<T> m_pendingOut;
	TSQueue<OwnedMsg<T>> &m_pendingIn;
	T m_tempIn;
	Owner m_owner;
};

template <class T>
const std::string_view Connection<T>::CATEGORY = "[CONNECTION]\t";

template <class T>
Connection<T>::Connection(Owner parent, boost::asio::io_context &context,
	boost::asio::ip::tcp::socket socket, TSQueue<OwnedMsg<T>> &inQueue):
		m_socket(std::move(socket)),
		m_ctx(context),
		m_pendingIn(inQueue),
		m_owner(parent)
{
}

template <class T>
Connection<T>::~Connection()
{
}

template <class T>
boost::asio::awaitable<void> Connection<T>::ConnectToServer(boost::asio::ip::tcp::resolver::results_type &&endpoints)
{
	if (m_owner != Owner::Client) return;

	boost::asio::async_connect(m_socket, endpoints,
		[this](std::error_code ec, boost::asio::ip::tcp::endpoint endpoint)
		{
			if (ec)
			{
				m_socket.close();
				OnError(std::move(ec));
			}
			else
				OnAccept();
		});
}

template <class T>
void Connection<T>::ConnectToClient()
{
	if (m_owner != Owner::Server) return;
	if (!IsConnected()) return;

	OnAccept();
}

template <class T>
bool Connection<T>::IsConnected() const
{
	return m_socket.is_open();
}

template <class T>
void Connection<T>::Disconnect()
{
	if (!IsConnected()) return;

	OnDisconnect();

	boost::asio::post(m_ctx, [this]()
	{
		m_socket.close();
	});
}

template <class T>
std::string Connection<T>::GetAddressStr() const
{
	return m_socket.remote_endpoint().address().to_string();
}

template <class T>
void Connection<T>::OnError(std::error_code &&)
{
}

template <class T>
void Connection<T>::OnAccept()
{
}

template <class T>
void Connection<T>::OnDisconnect()
{
}

template <class T>
void Connection<T>::OnPing()
{
}

template <class T>
void Connection<T>::Send(const T &msg)
{
}

template <class T>
void Connection<T>::TakeAndSend(T &&msg)
{
}

template <class T>
void Connection<T>::AddToQueue(T &&msg)
{
	if (m_owner == Owner::Client)
		m_pendingIn.PushBack({ nullptr, msg });
	else
		m_pendingIn.PushBack({ this->shared_from_this(), msg });
}

#endif // _CONNECTION_H
