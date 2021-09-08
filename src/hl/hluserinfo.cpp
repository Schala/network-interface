#include <boost/endian/conversion.hpp>

#include "hluserinfo.hpp"

namespace be = boost::endian;

HLUserInfo::HLUserInfo(std::istream &buf)
{
	buf.read(reinterpret_cast<char *>(&m_header.id), 2);
	buf.read(reinterpret_cast<char *>(&m_header.iconID), 2);
	m_header.flags = HLSessionFlags(buf);
	buf.read(reinterpret_cast<char *>(&m_header.nameSize), 2);

	be::big_to_native_inplace(m_header.id);
	be::big_to_native_inplace(m_header.iconID);
	be::big_to_native_inplace(m_header.nameSize);

	m_name.resize(m_header.nameSize, 0);
	buf.read(&m_name[0], m_header.nameSize);
}

std::string& HLUserInfo::GetName()
{
	return m_name;
}

void HLUserInfo::SetName(const std::string &name)
{
	m_name = name;
	m_header.nameSize = static_cast<uint16_t>(name.size());
}

uint16_t HLUserInfo::GetUserID() const
{
	return m_header.id;
}

void HLUserInfo::SetUserID(uint16_t id)
{
	m_header.iconID = id;
}

uint16_t HLUserInfo::GetNameSize() const
{
	return m_header.nameSize;
}

void HLUserInfo::SetIconID(uint16_t id)
{
	m_header.iconID = id;
}

std::ostream& operator<<(std::ostream &buf, const HLUserInfo &info)
{
	HLUserInfoHeader tmp;

	tmp.id = be::native_to_big(info.m_header.id);
	tmp.iconID = be::native_to_big(info.m_header.iconID);
	tmp.flags = info.m_header.flags;
	tmp.nameSize = be::native_to_big(info.m_header.nameSize);

	buf.write(reinterpret_cast<const char *>(&tmp.id), 2);
	buf.write(reinterpret_cast<const char *>(&tmp.iconID), 2);
	buf << tmp.flags;
	buf.write(reinterpret_cast<const char *>(&tmp.nameSize), 2);
	buf.write(info.m_name.data(), info.m_header.nameSize);
}
