#ifndef _HLSERVERTRACKERSESSION_H
#define _HLSERVERTRACKERSESSION_H

#include <set>
#include <string>
#include <vector>

#include "../session.hpp"

struct HLServerTrackerMsgHeader
{
	uint16_t type; // always 1?
	uint16_t port;
	uint16_t numUsers;
	uint16_t flags;
	uint32_t passID;
};

class HLServerTrackerMessage
{
private:
	std::string m_desc;
	std::string m_login;
	std::vector<uint8_t> m_password;
	HLServerTrackerMsgHeader m_header;
};

class HLServerTrackerSession : public SessionBase<HLServerTrackerMessage, boost::asio::ip::udp>
{
private:
	HLServerTrackerMessage m_msg;
};

typedef std::shared_ptr<HLServerTrackerSession> HLServerTrackerSessionPtr;
typedef std::set<HLServerTrackerSessionPtr> HLServerTrackerSessionSet;

#endif // _HLSERVERTRACKERSESSION_H