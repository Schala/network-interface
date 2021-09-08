#include <boost/endian/conversion.hpp>
#include <cctype>
#include <cstring>
#include <format>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <utility>

#include "../macros.h"
#include "hlsession.hpp"
#include "hlutils.hpp"

namespace be = boost::endian;
namespace io = boost::asio;

static const uint32_t TRTP = CODE('TRTP');

HLSession::HLSession(uint16_t id, SessionOwner owner, boost::asio::ip::tcp::socket socket, boost::asio::io_context &ctx,
	NetQueue<PacketType> &inQueue):
	SessionBase(owner, ctx, inQueue),
	m_sock(std::move(socket)),
	m_account(HLAccount::Null),
	m_loginTime(std::chrono::system_clock::now()),
	m_lastTransID(0)
{
	m_timer = boost::asio::steady_timer(m_sock.get_executor());
	m_timer.expires_at(std::chrono::steady_clock::time_point::max());
	m_info.SetUserID(id);
}

HLSession::~HLSession()
{
	Disconnect();
}

void HLSession::Start()
{
	io::co_spawn(m_sock.get_executor(),
		[self = GetSharedPtr()]
		{
			return self->Read();
		}, io::detached);
	
	io::co_spawn(m_sock.get_executor(),
		[self = GetSharedPtr()]
		{
			return self->Write();
		}, io::detached);
}

void HLSession::SendAll(const HLTransaction &msg, bool ignoreSelf)
{
}

void HLSession::Disconnect()
{
	SessionBase::Disconnect();
	m_sock.close();
}

bool HLSession::IsConnected() const
{
	return m_sock.is_open();
}

void HLSession::OnException(const std::string &what)
{
}

void HLSession::OnError(const std::error_code &ec)
{
}

boost::asio::awaitable<void> HLSession::Read()
{
	try
	{
		// First, read the greeting
		{
			HLClientHello clientHello;
			std::memset(&clientHello, 0, 12);
			co_await io::async_read(m_sock, io::buffer(&clientHello, 12), io::use_awaitable);

			be::big_to_native_inplace(clientHello.protocol);
			be::big_to_native_inplace(clientHello.version);

			// Reply if valid, or drop the connection if invalid
			if (clientHello.protocol == TRTP && ((clientHello.version & 0xFFFF0000) >> 16) == 1)
			{
				HLServerHello serverHello { be::native_to_big(TRTP), 0 };
				co_await io::async_write(m_sock, io::buffer(&serverHello, 8), io::use_awaitable);
			}
			else
				m_sock.close();
		}

		// If the greeting succeeds, loop for transactions
		while (IsConnected())
		{
			HLTransactionHeader header;
			co_await io::async_read(m_sock, io::buffer(&header, 20), io::use_awaitable);

			if (header.chunkSize > 0)
			{
				size_t n = co_await io::async_read(m_sock, m_inBuf, io::use_awaitable);

				if (n < header.chunkSize)
					throw std::runtime_error(std::format("Expected {} bytes, but got {}", header.chunkSize, n));
				
				m_in.Push(HLTransaction(header, std::istream(&m_inBuf)));
				m_inBuf.consume(n);
			}
			else
				m_in.Push({ GetSharedPtr(), HLTransaction(header) });
		}
	}
	catch (std::exception &e)
	{
		OnException(e.what());
	}
}

boost::asio::awaitable<void> HLSession::Write()
{
	using io = boost::asio;

	try
	{
		while (IsConnected())
		{
			if (m_out.IsEmpty())
			{
				std::error_code ec;
				co_await m_timer.async_wait(io::redirect_error(io::use_awaitable, ec));
				if (ec) OnError(ec);
			}
			else
			{
				PacketType p = m_out.Pop();
				co_await io::async_write(m_sock, io::buffer(), io::use_awaitable);
			}
		}
	}
	catch (std::exception &e)
	{
		OnException(e.what());
	}
}

std::shared_ptr<HLSession> HLSession::GetSharedPtr() const
{
	return std::static_pointer_cast<HLSession>(shared_from_this());
}

uint32_t HLSession::GetNewTransactionID()
{
	return ++m_lastTransID;
}

uint32_t HLSession::GetCurrentTransactionID() const
{
	return m_lastTransID;
}

uint16_t HLSession::GetUserID() const
{
	return m_info.GetID();
}

void HLSession::SetVersion(uint16_t version)
{
	m_version = version;
}

uint16_t HLSession::GetVersion() const
{
	return m_version;
}

bool HLSession::ValidateLogin(const HLAccountSet &accounts, const std::string &login,
	const ByteString &password)
{
	bool validLogin = false;
	std::string myLogin = login;
	HLAccountPtr validAccount = HLAccount::Null;
	std::optional<std::vector<uint8_t>> accountPassword = std::nullopt;

	// login could be encoded, so test it and decode if necessary
	bool encodedLogin = std::any_of(myLogin.begin(), myLogin.end(), [](char c)
	{
		return !(c == '_' || std::isalnum(c))
	});
	if (encodedLogin) Crypt(myLogin);

	// check for the specified login
	for (auto &a : accounts)
	{
		if (a->GetLogin() == myLogin)
		{
			validLogin = true;
			validAccount = a;
			accountPassword = a->GetPassword();
			break;
		}
	}
	if (!validLogin) return false;

	// validate password, if there is one
	if (accountPassword && !password.empty())
	{
		if (accountPassword->size() == password.size()))
			for (int i = 0; i < accountPassword->size()
				if (accountPassword->at(i) != password.at(i))
					return false;
		else
			return false;
	}
	else
		if (!password.empty())
			return false;
	
	// success
	m_account = validAccount;
	return true;
}

HLAccountPtr HLSession::GetAccount() const
{
	return m_account.lock();
}

void HLSession::SetName(const std::string &name)
{
	m_info.SetName(name);
}

void HLSession::SetIconID(uint16_t id)
{
	m_info.SetIconID(id);
}

void HLSession::SetMessageFlags(HLMessageFlags flags)
{
	m_msgFlags = flags;
}

void HLSession::SetAutoReply(const std::string &message)
{
	m_autoReply = message;
}

HLUserAccess HLSession::GetAccess() const
{
	return m_account.lock()->GetUserAccess();
}

HLUserInfo HLSession::GetUserInfo() const
{
	return m_info;
}
