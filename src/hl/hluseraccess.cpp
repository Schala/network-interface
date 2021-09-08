#include <boost/endian/conversion.hpp>

#include "hluseraccess.hpp"

HLUserAccess::HLUserAccess(uint64_t access):
	m_opaque(boost::endian::big_to_native(access))
{
}

HLUserAccess::HLUserAccess(std::istream &buf)
{
	using be = boost::endian;

	buf.read(reinterpret_cast<char *>(&m_opaque), 8);
	be::big_to_native_inplace(m_opaque);
}

std::ostream& operator<<(std::ostream &buf, HLUserAccess access)
{
	using be = boost::endian;
	uint64_t opaque = be::native_to_big(access.m_opaque);

	buf.write(reinterpret_cast<const char *>(&opaque), 8);
}

bool HLUserAccess::DontShowAgreement() const
{
	return m_bits.noAgreement;
}
