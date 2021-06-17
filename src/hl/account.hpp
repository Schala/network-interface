#ifndef _HL_ACCOUNT_H
#define _HL_ACCOUNT_H

#include <bitset>
#include <boost/predef.h>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace ACCESS
{
	enum
	{
		ALL
	};
}

class Account : public std::enable_shared_from_this<Account>
{
private:
	std::string m_name;
	std::string m_login;
	std::vector<uint8_t> m_pw;
	std::bitset<ACCESS::ALL> m_access;
	uint16_t m_icon;
};

#endif // _HL_ACCOUNT_H
