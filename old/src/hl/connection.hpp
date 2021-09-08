#ifndef _HL_CONNECTION_H
#define _HL_CONNECTION_H

#include <cstdint>
#include <string>
#include <vector>

#include "../connection.hpp"

struct MSG;

class HLConnection : public Connection<MSG>
{
private:
	std::string m_name;
	std::vector<uint8_t> m_gif;
	uint16_t m_id;
	uint16_t m_icon;
	uint16_t m_flags;
	uint16_t m_ver;
};

#endif // _HL_CONNECTION_H
