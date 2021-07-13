#ifndef _HL_ACCOUNT_H
#define _HL_ACCOUNT_H

#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

class HLAccount : public std::enable_shared_from_this<HLAccount>
{
private:
	std::mutex m_mutex;
	std::string m_name;
	std::string m_login;
	std::vector<uint8_t> m_pw;
	uint16_t m_icon;
	uint16_t m_colour;
};

#endif // _HL_ACCOUNT_H
