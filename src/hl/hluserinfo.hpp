#ifndef _HLUSERINFO_H
#define _HLUSERINFO_H

#include <string>

#include "hluserflags.hpp"

struct HLUserInfoHeader
{
	HLUserInfoHeader() = default;

	uint16_t id;
	uint16_t iconID;
	HLSessionFlags flags;
	uint16_t nameSize;
};

class HLUserInfo
{
	friend std::ostream& operator<<(std::ostream &buf, const HLUserInfo &info);
public:
	// For session default construction
	HLUserInfo() = default;

	// For GetUserInfo transactions
	HLUserInfo(std::istream &buf);
	std::string& GetName();
	void SetName(const std::string &name);
	uint16_t GetUserID() const;
	void SetUserID(uint16_t id);
	void SetIconID(uint16_t id);
	uint16_t GetNameSize() const;
private:
	HLUserInfoHeader m_header;
	std::string m_name;
};

std::ostream& operator<<(std::ostream &buf, const HLUserInfo &info);

#endif // _HLUSERINFO_H
