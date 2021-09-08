#ifndef _HLUSERFLAGS_H
#define _HLUSERFLAGS_H

#include <cstdint>
#include <istream>
#include <ostream>

class HLSessionFlags
{
	friend std::ostream& operator<<(std::ostream &buf, HLSessionFlags flags);
public:
	HLSessionFlags(uint16_t flags);
	HLSessionFlags(std::istream &buf);
private:
	union
	{
		uint16_t m_opaque;

		struct
		{
			uint16_t
				away : 1,
				admin : 1,
				refuseMessages : 1,
				refuseChats : 1;
		} m_bits;
	};
};

class HLMessageFlags
{
	friend std::ostream& operator<<(std::ostream &buf, HLMessageFlags flags);
public:
	HLMessageFlags(uint16_t flags);
	HLMessageFlags(std::istream &buf);
private:
	union
	{
		uint16_t m_opaque;

		struct
		{
			uint16_t
				refuseMessages : 1,
				refusePrivateChat : 1,
				autoReply : 1;
		} m_bits;
	};
};

std::ostream& operator<<(std::ostream &buf, HLSessionFlags flags);
std::ostream& operator<<(std::ostream &buf, HLMessageFlags flags);

#endif // _HLUSERFLAGS_H
