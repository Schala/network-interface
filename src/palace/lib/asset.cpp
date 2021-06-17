#include "asset.hpp"
#include "protocol.hpp"

Asset& Asset::GetSpec(AssetSpec &spec) const
{
	spec = m_spec;
	return *this;
}

Asset& Asset::GetFlags(PROP_FLAGS &flags) const
{
	flags = m_flags;
	return *this;
}

Asset& Asset::GetName(Str31 &name) const
{
	name.Set(m_name);
	return *this;
}

Asset& Asset::GetType(uint32_t &type) const
{
	type = m_type;
	return *this;
}

Asset& Asset::SetSpec(const AssetSpec &spec)
{
	m_spec = spec;
	return *this;
}

Asset& Asset::SetFlags(const PROP_FLAGS &flags)
{
	m_flags = flags;
	return *this;
}

Asset& Asset::SetName(const char *name)
{
	m_name.Set(name);
	return *this;
}

uint32_t Asset::GenCRC()
{
	m_spec.crc = MAGIC;
	for (auto b : m_data)
		m_spec.crc = ((m_spec.crc << 1) | ((m_spec.crc & 0x80000000) ? 1 : 0)) ^ b;
	return m_spec.crc;
}
