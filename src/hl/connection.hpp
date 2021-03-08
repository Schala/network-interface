#ifndef _HL_CONNECTION_H
#define _HL_CONNECTION_H

#include <string>

#include "../connection.hpp"

namespace cmm
{
	struct message;

	class hl_connection : public connection<message>
	{
	private:
		std::string name_;
		uint16 icon_;
		uint16 version_;
	};
};

#endif // _HL_CONNECTION_H
