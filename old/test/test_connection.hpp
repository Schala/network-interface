#ifndef _TEST_CONNECTION_H
#define _TEST_CONNECTION_H

#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <system_error>

#include "../src/connection.hpp"

class TestConnection : public Connection<std::string>
{
public:
	TestConnection(Owner parent, boost::asio::io_context &context,
		boost::asio::ip::tcp::socket socket, TSQueue<OwnedMsg<std::string>> &inQueue):
			Connection<std::string>(parent, context, std::move(socket), inQueue)
	{
	}
	
	void OnAccept() override
	{
#ifdef BUILD_CLIENT
		std::cout << "Connected successfully" << std::endl;
#endif
		HandleRead();
	}

	void OnDisconnect()
	{
	}

	void Send(const std::string &msg) override
	{
		boost::asio::post(m_ctx, [this, &msg]()
		{
			bool empty = m_pendingOut.IsEmpty();
			m_pendingOut.PushBack(msg);
			if (empty) HandleWrite();
		});
	}

	void TakeAndSend(std::string &&msg) override
	{
		boost::asio::post(m_ctx, [this, message = std::move(msg)]()
		{
			bool empty = m_pendingOut.IsEmpty();
			m_pendingOut.PushBack(message);
			if (empty) HandleWrite();
		});
	}

	void HandleRead()
	{
		m_tempIn.resize(1024);

		boost::asio::async_read(m_socket, boost::asio::buffer(m_tempIn, 1024),
			[this](std::error_code ec, std::size_t length)
			{
				if (ec)
				{
					m_socket.close();
					OnError(std::move(ec));
				}
				else
				{
					AddToQueue(std::move(m_tempIn));
					HandleRead();
				}
			});
	}

	void HandleWrite()
	{
		boost::asio::async_write(m_socket, boost::asio::buffer(m_pendingOut.Front(),
			m_pendingOut.Front().size()), [this](std::error_code ec, std::size_t length)
			{
				if (ec)
				{
					auto msg = m_pendingOut.PopFront();
#ifdef BUILD_SERVER
					S_LOG.WriteMsg(CATEGORY, LogLevel::Error,
						std::format("Unable to send message of length {}: {}", length, msg));
#else
					std::cerr << std::format("Unable to send message of length {}: {}", length, msg) << std::endl;
#endif // BUILD_SERVER
				}
				else
					m_pendingOut.PopFront();
				
				if (!m_pendingOut.IsEmpty()) HandleWrite();
			});
	}

	void OnError(std::error_code &&) override
	{
		std::cout << "Aw fuck!" << std::endl;
#ifdef BUILD_CLIENT
		std::exit(1);
#endif
	}
};

#endif // _TEST_CONNECTION_H
