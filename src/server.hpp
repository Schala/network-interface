#ifndef _SERVER_H
#define _SERVER_H

#include <algorithm>
#include <exception>
#include <iostream>
#include <system_error>
#include <thread>
#include <utility>

#include "connection.hpp"

#define _CMM_SERVER_BUILD

namespace cmm
{
	template <class T> class server_interface
	{
	public:
		server_interface(uint16 port):
			acceptor_(context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
		{
		}

		virtual ~server_interface()
		{
			stop();
		}

		bool start()
		{
			try
			{
				wait(); // issue work BEFORE starting context, or it will exit immediately

				context_thread_ = std::thread([this]()
				{
					context_.run();
				});
			}
			catch (std::exception &e_)
			{
				std::cerr << "Failed to start:" << e_.what() << std::endl;
				return false;
			}

			std::cout << "Server started" << std::endl;
			return true;
		}

		void stop()
		{
			context_.stop();
			if (context_thread_.joinable()) context_thread_.join();
			std::cout << "Server stopped" << std::endl;
		}

		void wait()
		{
			acceptor_.async_accept(
				[this](std::error_code ec_, boost::asio::ip::tcp::socket socket_)
				{
					if (ec_)
						std::cout << "Connection error: " << ec_.message() << std::endl;
					else
					{
						std::cout << "New connection: " << socket_.remote_endpoint() << std::endl;
						auto conn_ =
							std::make_shared<connection<T>>(connection<T>::owner::server, context_,
								std::move(socket_), pending_in_);
						
						if (on_client_connect(conn_))
							connections_.push_back(std::move(conn_));
						else
							std::cout << "Connection denied." << std::endl;
					}

					wait();
				});
		}

		void send(std::shared_ptr<connection<T>> client, const T &msg)
		{
			if (client && client->is_connected())
				client->send(msg);
			else
			{
				on_client_disconnect(client);
				client.reset();
				connections_.erase(std::remove(connections_.begin(), connections_.end(), client),
					connections_.end());
			}
		}

		void send_all(const T &msg, std::shared_ptr<connection<T>> ignore = nullptr)
		{
			bool invalid_client_found_ = false;

			for (auto &client_ : connections_)
			{
				if (client_ && client_->is_connected())
				{
					if (client_ != ignore)
						client_->send(msg);
				}
				else
				{
					on_client_disconnect(client_);
					client_.reset();
					invalid_client_found_ = true;
				}
			}

			if (invalid_client_found_)
				connections_.erase(std::remove(connections_.begin(), connections_.end(), nullptr));
		}

		void update(sizeint max_messages = -1)
		{
			sizeint msg_count_ = 0;

			while (msg_count_++ < max_messages && !pending_in_.empty())
			{
				auto msg = pending_in_.pop_front();
				on_receive(msg.remote, msg.data);
			}
		}
	protected:
		tsqueue<owned_message<T>> pending_in_;
		std::deque<std::shared_ptr<connection<T>>> connections_;
		boost::asio::io_context context_;
		std::thread context_thread_;
		boost::asio::ip::tcp::acceptor acceptor_;

		virtual bool on_client_connect(std::shared_ptr<connection<T>> client)
		{
			return false;
		}

		virtual void on_client_disconnect(std::shared_ptr<connection<T>> client)
		{
		}

		virtual void on_receive(std::shared_ptr<connection<T>> client, T &msg)
		{
		}
	};
}

#endif // _SERVER_H
