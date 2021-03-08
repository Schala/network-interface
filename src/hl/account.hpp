#ifndef _HL_ACCOUNT_H
#define _HL_ACCOUNT_H

#include <bitset>
#include <boost/predef.h>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "../common.hpp"

namespace cmm
{
	namespace access
	{
		enum
		{
			all
		};
	}

	class account : public std::enable_shared_from_this<account>
	{
	private:
		std::string name_;
		std::string login_;
		std::vector<uint8> password_;
		std::bitset<access::all> access_;
	};
}

#endif // _HL_ACCOUNT_H
