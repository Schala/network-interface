#ifndef _LOE_CONNECTION_H
#define _LOE_CONNECTION_H

#include <bitset>

#include "../connection.hpp"

namespace cmm
{
	struct pony;

	class loe_connection
	{
	private:
		std::vector<std::shared_ptr<pony>> ponies_;
		float last_ping_time_;
		int32 last_ping_num_;
		uint16 received_packet_dups_;
	};

	namespace race
	{
		enum
		{
			none = 0,
			earth,
			unicorn,
			pegasus,
			moose,
			crystal,
			gryphon,
			all
		};
	};

	struct pony
	{
		std::shared_ptr<loe_connection> owner;
		std::bitset<race::all> race;
		std::string name;
		uint32 bits;
	};
};

#endif // _LOE_CONNECTION_H
