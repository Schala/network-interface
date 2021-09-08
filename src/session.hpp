#ifndef _SESSION_H
#define _SESSION_H

#include <boost/asio.hpp>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <memory>
#include <system_error>

#include "netqueue.hpp"

template <class Msg, class Protocol> struct Packet;

enum class SessionOwner : uint8_t
{
	Server, Client
};

// Base class of sessions, which encapsulate the I/O functionality between a client and server
// This intentionally lacks a socket variable in case derivatives decide to use an SSL wrapper.
template <class Msg, class Protocol>
class SessionBase : public std::enable_shared_from_this<SessionBase<Msg, Protocol>>
{
public:
	typedef Packet<Msg, Protocol> PacketType;
	typedef Protocol::resolver::results_type ResolvedEndpointsType;
	typedef Protocol::endpoint EndpointType;

	// Client-side connection establish asynchronously. This is suitable for GUI clients or servers
	// that have an internal client
	//virtual void ConnectToServerAsync(const ResolvedEndpointsType &endpoints);

	// To be called after construction
	virtual void Start();

	// Close the socket
	virtual void Disconnect();

	// Are we connected?
	virtual bool IsConnected() const;

	// Sends a packet of data to the remote endpoint
	virtual void Send(const Msg &msg);
protected:
	boost::asio::io_context &m_ctx;
	boost::asio::steady_timer m_timer;
	std::chrono::system_clock::time_point m_idle;
	NetQueue<PacketType> m_out;
	NetQueue<PacketType> &m_in;
	boost::asio::streambuf m_inBuf;
	boost::asio::streambuf m_outBuf;
	SessionOwner m_owner;

	// Should only be called by derived class constructors
	SessionBase(SessionOwner owner, boost::asio::io_context &ctx, NetQueue<PacketType> &inQueue);

	// Adds a new data message to the write queue
	void AddToQueue(const Msg &msg);

	// Called by the client once connection has established
	virtual bool OnConnect();

	// Called if an error occurs, with the error code provided
	virtual void OnError(const std::error_code &ec);

	// Called if an error occurs, with the error code and endpoint provided
	virtual void OnError(const std::error_code &ec, const EndpointType &ep);

	// Called when an exception occurs
	virtual void OnException(const std::string &what);

	// Called before connection is closed
	virtual void OnDisconnect();
};

/*template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::ConnectToServerAsync(const ResolvedEndpointsType &endpoints)
{
	boost::asio::async_connect(m_sock, endpoints,
		[this](std::error_code ec, EndpointType ep)
		{
			if (ec)
			{
				OnError(ec, ep);
				Disconnect();
			}
			else
			{
				if (!OnConnect())
					Disconnect();
			}
		});
}*/

// Session class constraint
template <class T, class Msg, class Protocol>
concept Session = std::derived_from<T, SessionBase<Msg, Protocol>>;


template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::Disconnect()
{
	if (!IsConnected()) return;

	OnDisconnect();
}

template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::Start()
{
}

template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::OnException(const std::string &what)
{
}

template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::Send(const Msg &msg)
{
	m_out.Push({ this.shared_from_this(), msg });
	m_timer.cancel_one();
}

template <class Msg, class Protocol>
bool SessionBase<Msg, Protocol>::IsConnected() const
{
	return false;
}

template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::AddToQueue(const Msg &msg)
{
	if (m_owner == SessionOwner::Client)
		m_in.Push({ nullptr, msg });
	else
		m_in.Push({ this->shared_from_this(), msg });
}

template <class Msg, class Protocol>
SessionBase<Msg, Protocol>::SessionBase(SessionOwner owner, boost::asio::io_context &ctx,
		NetQueue<PacketType> &inQueue):
	m_ctx(ctx),
	m_idle(std::chrono::system_clock::now()),
	m_in(inQueue),
	m_owner(owner)
{
}

template <class Msg, class Protocol>
bool SessionBase<Msg, Protocol>::OnConnect()
{
	return true;
}

template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::OnError(const std::error_code &)
{
}

template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::OnError(const std::error_code &, const EndpointType &)
{
}

template <class Msg, class Protocol>
void SessionBase<Msg, Protocol>::OnDisconnect()
{
}

#endif // _SESSION_H
