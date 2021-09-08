#ifndef _HLDATETIME_H
#define _HLDATETIME_H

#include <chrono>
#include <cstdint>
#include <vector>

class HLDateTime
{
public:
	static HLDateTime Now();
	HLDateTime(const std::chrono::system_clock::time_point &tp);
	HLDateTime(uint64_t ticks);
	HLDateTime(const std::vector<uint8_t> &buffer);
	std::chrono::system_clock::time_point GetTimePoint() const;
	uint64_t GetTicks() const;
private:
	uint16_t m_year;
	uint16_t m_msecs;
	uint32_t m_secs;
};

#endif // _HLDATETIME_H
