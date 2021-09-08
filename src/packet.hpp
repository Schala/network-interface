#ifndef _PACKET_H
#define _PACKET_H

#include "session.hpp"

// A packet of data, holding an owning session and data
template <class Msg, class Protocol>
struct Packet
{
	std::shared_ptr<Session<Msg, Protocol>> owner;
	Msg data;
};

#endif // _PACKET_H
