#include <boost/endian/conversion.hpp>

#include "hluserflags.hpp"

HLSessionFlags::HLSessionFlags(uint16_t flags):
	m_opaque(boost::endian::big_to_native(flags))
{
}

HLSessionFlags::HLSessionFlags(std::istream &buf)
{
	using be = boost::endian;

	buf.read(reinterpret_cast<char *>(&m_opaque), 2);
	be::big_to_native_inplace(m_opaque);
}

HLMessageFlags::HLMessageFlags(uint16_t flags):
	m_opaque(boost::endian::big_to_native(flags))
{
}

HLMessageFlags::HLMessageFlags(std::istream &buf)
{
	using be = boost::endian;

	buf.read(reinterpret_cast<char *>(&m_opaque), 2);
	be::big_to_native_inplace(m_opaque);
}

std::ostream& operator<<(std::ostream &buf, HLSessionFlags flags)
{
	using be = boost::endian;
	uint16_t opaque = be::native_to_big(flags.m_opaque);

	buf.write(reinterpret_cast<const char *>(&opaque), 2);
}

std::ostream& operator<<(std::ostream &buf, HLMessageFlags flags)
{
	using be = boost::endian;
	uint16_t opaque = be::native_to_big(flags.m_opaque);

	buf.write(reinterpret_cast<const char *>(&opaque), 2);
}
