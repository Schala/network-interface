#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <boost/asio.hpp>
#include <memory>
#include <utility>

#include "owned_message.hpp"
#include "tsqueue.hpp"

namespace cmm
{
	/// A connection between a client and a server
	template <class T> class connection : public std::enable_shared_from_this<connection<T>>
	{
	public:
		enum class owner : uint8
		{
			server = 0,
			client
		};

		connection(owner parent, boost::asio::io_context &context,
			boost::asio::ip::tcp::socket socket, tsqueue<owned_message<T>> &in_queue):
			socket_(std::move(socket)), context_(context), pending_in_(in_queue), owner_(parent)
		{
		}

		virtual ~connection()
		{
		}

		bool connect()
		{
		}

		bool disconnect()
		{
		}

		bool is_connected() const
		{
			return socket_.is_open();
		}

		bool send(const T &msg)
		{
		}

#ifdef _CMM_SERVER_BUILD
		void push_temp()
		{
			pending_in_.push_back({ this->shared_from_this(), temp_in_ });
		}
#endif // _CMM_SERVER_BUILD
	protected:
		boost::asio::ip::tcp::socket socket_;
		boost::asio::io_context &context_;
		tsqueue<T> pending_out_;
		tsqueue<owned_message<T>> &pending_in_;
		T temp_in_;
		owner owner_;
	};
}

#endif // _CONNECTION_H
