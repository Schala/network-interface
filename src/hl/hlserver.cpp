#include <algorithm>

#include "hlserver.hpp"

namespace io = boost::asio;

static const std::string_view BadData = "Malformed or unsupported packet data received.";

HLServer::HLServer(uint16_t port, size_t numThreads):
	ServerBase<HLTransaction, boost::asio::ip::tcp>(numThreads),
	m_acceptor(m_ctx, { boost::asio::ip::tcp::v4(), port }),
	m_lastIssuedID(0)
{
}

HLServer::~HLServer()
{
}

void HLServer::Run()
{
	io::signal_set signals(m_ctx, SIGINT, SIGTERM);

	io::co_spawn(m_ctx, Listen(), io::detached);
	io::co_spawn(m_ctx, ProcessQueue(), io::detached);

	signals.async_wait([this](const std::error_code &, int)
	{
		Stop();
	});
	ServerBase<HLTransaction, io::ip::tcp>::Run();
}

void HLServer::OnStop()
{
}

void HLServer::Send(HLSessionPtr user, const HLTransaction &trans)
{
	if (user && user->IsConnected())
		user->Send(trans);
	else
		m_clientSessions.erase(user->GetUserID());
}

void HLServer::SendAll(HLTransaction &trans, const HLSessionPtr &ignore)
{
	bool ghostFound = false;

	for (auto &[id, user] : m_clientSessions)
	{
		if (user && user->IsConnected())
			if (user != ignore)
			{
				trans.id = user->GetNewTransactionID();
				user->Send(trans);
			}
		else
		{
			user.reset();
			ghostFound = true;
		}
	}

	if (ghostFound) PurgeGhosts();
}

void HLServer::PurgeGhosts()
{
	for (auto &[id, user] : m_clientSessions)
		if (!user) m_clientSessions.erase(user);
}

boost::asio::awaitable<void> HLServer::Listen()
{
	while (m_acceptor.is_open())
	{
		std::make_shared<HLSession>(++m_lastIssuedID, SessionOwner::Server,
			co_await m_acceptor.async_accept(io::use_awaitable), m_ctx,
			m_in)->Start();
	}
}

boost::asio::awaitable<void> HLServer::ProcessQueue()
{
	while (!m_ctx.stopped())
	{
		if (!m_in.IsEmpty())
		{
			auto p = m_in.Pop();

			if (p.owner && p.owner->IsConnected())
			{
				switch (p.data.GetOpcode())
				{
					case HLOpcode::Login: HandleLogin(p); break;
					case HLOpcode::Agreed: HandleAgreed(p); break;
					case HLOpcode::UserNameListGet: HandleGetUserNameList(p); break;
					default:
						HandleError(p.owner, BadData);
				}
			}
			else
				m_clientSessions.erase(p.owner->GetUserID());
		}
	}
}

void HLServer::HandleLogin(const PacketType &p)
{
	switch (p.data.GetParamCount())
	{
		case 1: // should be a version param, the default guest login
			if (p.data[0].GetID() == HLParamID::Version)
			{
				p.owner->SetVersion(std::get<uint16_t>(p.data[0].GetData());
				SendLoginReply(p.owner);
			}
			else
				HandleError(p.owner, BadData);
			break;
		case 3: // should be login -> password -> version, in that order
			if ((p.data[0].GetID() == HLParamID::UserLogin) &&
				(p.data[1].GetID() == HLParamID::UserPassword) &&
				(p.data[2].GetID() == HLParamID::Version))
			{
				if (p.owner->ValidateLogin(m_accounts,
					std::get<std::string>(p.data[0].GetData()),
					std::get<ByteString>(p.data[1].GetData()));
				{
					p.owner->SetVersion(std::get<uint16_t>(p.data[0].GetData());
					SendLoginReply(p.owner);
				}
				else
					HandleError(p.owner, "Incorrect login and/or password");
			}
			else
				HandleError(p.owner, BadData);
			break;
		default:
			HandleError(p.owner, BadData);
	}
}

void HLServer::SendLoginReply(HLSessionPtr user)
{
	HLTransaction reply(HLOpcode::Reply, user->GetCurrentTransactionID());

	reply.AddParam(HLParamID::Version, Version);
	if (user->GetVersion() >= 151)
	{
		// We don't use banners because of a security flaw, so just send a value of 0
		reply.AddParam(HLParamID::BannerID, static_cast<uint16_t>(0));

		reply.AddParam(HLParamID::ServerName, m_name);
	}

	user->Send(reply);

	if (m_agreement.empty() || user->GetAccount()->DontShowAgreement())
	{
		HLTransaction noAgreement(HLOpcode::AgreementShow, false);
		user->Send(noAgreement);
	}
	else
	{
		// todo
	}
}

void HLServer::HandleAgreedDefault(const PacketType &p)
{
	if ((p.data[0].GetID() == HLParamID::UserName) &&
		(p.data[1].GetID() == HLParamID::UserIconID) &&
		(p.data[2].GetID() == HLParamID::ChatOptions))
	{
		p.owner->SetName(std::get<std::string>(p.data[0].GetData()));
		p.owner->SetIconID(std::get<uint16_t>(p.data[1].GetData()));
		p.owner->SeMessageFlags(std::get<HLMessageFlags>(p.data[2].GetData()));
	}
	else
		HandleError(p.owner, BadData);
}

void HLServer::HandleAgreed(const PacketType &p)
{
	switch (p.data.GetParamCount())
	{
		case 3: // should be name -> icon ID -> msg flags, in that order
			HandleAgreedDefault(p);
			SendReply(p.owner);
			SendUserAccess(p.owner);
			break;
		case 4: // message included an auto reply
			if (p.data[3].GetID() == HLParamID::AutoReply)
			{
				HandleAgreedDefault(p);
				p.owner.SetAutoReply(std::get<std::string>(p.data[0].GetData()));
				SendReply(p.owner);
				SendUserAccess(p.owner);
			}
			else
				HandleError(p.owner, BadData);
			break;
		default:
			HandleError(p.owner, BadData);
	}
}

void HLServer::SendReply(HLSessionPtr user)
{
	HLTransaction reply(HLOpcode::Reply, 0);
	user->Send(reply);
}

void HLServer::SendUserAccess(HLSessionPtr user)
{
	HLTransaction trans(HLOpcode::UserAccess, user->GetNextTransactionID());
	trans.AddParam(HLParamID::UserAccess, user->GetAccess());
	user->Send(trans);
}

void HLServer::HandleGetUserNameList(const PacketType &p)
{
	// should have no params
	if (p.data.GetParamCount() > 0)
	{
		HandleError(p.owner, BadData);
		return;
	}

	HLTransaction reply(HLOpcode::Reply, p.owner->GetCurrentTransactionID());

	for (auto &[id, user] : m_clientSessions)
	{
		bool ghostFound = false;

		if (user && user->IsConnected())
			reply.AddParam(HLParamID::UserInfo, user->GetUserInfo());
		else
		{
			user.reset();
			ghostFound = true;
		}
	}
	p.owner->Send(reply);
	
	if (ghostFound) PurgeGhosts();
}

void HLServer::HandleError(HLSessionPtr user, const std::string_view &message)
{
	// todo
}
