#ifndef _HL_MSG_H
#define _HL_MSG_H

#include <vector>

#include "protocol.hpp"

struct Parameter
{
	MSG_FIELD_HEADER header;
	std::vector<uint8_t> data;
};

struct Transaction
{
	MSG_HEADER header;
	std::vector<Parameter> params;
};

#endif // _HL_MSG_H
