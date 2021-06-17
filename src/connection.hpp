#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <memory>
#include <utility>

#include "owned_msg.hpp"
#include "tsqueue.hpp"

/// A connection between a client and a server
template <class T> class Connection : public std::enable_shared_from_this<Connection<T>>
{
public:
	enum class Owner : uint8_t
	{
		Server = 0,
		Client
	};

	Connection(Owner parent, boost::asio::io_context &context,
		boost::asio::ip::tcp::socket socket, TSQueue<OwnedMsg<T>> &inQueue);
	virtual ~Connection();
	bool Connect();
	bool Disconnect();
	bool IsConnected() const;
	bool Send(const T &msg);

#ifdef BUILD_SERVER
	void PushTemp();
#endif // BUILD_SERVER
protected:
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::io_context &m_ctx;
	TSQueue<T> m_pendingOut;
	TSQueue<OwnedMsg<T>> &m_pendingIn;
#ifdef BUILD_SERVER
	T m_tempIn;
#endif // BUILD_SERVER
	Owner m_owner;
};

template <class T>
Connection<T>::Connection(Owner parent, boost::asio::io_context &context,
	boost::asio::ip::tcp::socket socket, TSQueue<OwnedMsg<T>> &inQueue):
	m_socket(std::move(socket)), m_ctx(context), m_pendingIn(inQueue), m_owner(parent)
{
}

template <class T>
Connection<T>::~Connection()
{
}

template <class T>
bool Connection<T>::Connect()
{
	return true;
}

template <class T>
bool Connection<T>::Disconnect()
{
	return true;
}

template <class T>
bool Connection<T>::IsConnected() const
{
	return m_socket.is_open();
}

template <class T>
bool Connection<T>::Send(const T &msg)
{
	return true;
}

#ifdef BUILD_SERVER
template <class T>
void Connection<T>::PushTemp()
{
	m_pendingIn.push_back({ this->shared_from_this(), m_tempIn });
}
#endif // BUILD_SERVER


#endif // _CONNECTION_H
