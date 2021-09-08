#include <algorithm>
#include <cstring> // for ugly memmove workaround for POD read/write
#include <utility>

#include "message.hpp"
#include "protocol.hpp"

PalaceMessage::PalaceMessage(std::vector<uint8_t> &incoming):
	m_write(m_data) // stop the compiler from whining
{
	m_data = std::move(incoming);
	Get(m_header);
}

PalaceMessage::PalaceMessage(uint32_t event, int32_t ref):
	m_write(m_data)
{
	m_header.event = event;
	m_header.ref = ref;
}

template <class T>
PalaceMessage& PalaceMessage::Get(T &t)
{
	std::memcpy(&t, &(*m_read), sizeof(T));
	std::advance(m_read, sizeof(T));
	return *this;
}

PalaceMessage& PalaceMessage::GetCStr(std::string &s)
{
	char c = ' ';
	
	while (c != 0)
	{
		c = static_cast<char>(*(m_read++));
		s += c;
	}

	return *this;
}

PalaceMessage& PalaceMessage::GetPStr(std::string &s)
{
	uint8_t len = static_cast<uint8_t>(*m_read++);
	s.resize(len);

	std::copy_n(m_read, len, s.begin());
	m_read += len;
	return *this;
}

PalaceMessage& PalaceMessage::GetData(std::vector<uint8_t> &data, size_t length)
{
	data.resize(length);
	std::copy_n(m_read, length, data.begin());
	m_read += length;
	return *this;
}

template <class T> PalaceMessage& PalaceMessage::Put(T t)
{
	std::memcpy(&(*m_write), sizeof(T), &t);
	std::advance(m_write, sizeof(T));
	return *this;
}

PalaceMessage& PalaceMessage::PutCStr(std::string_view s)
{
	std::copy(s.begin(), s.end(), m_write);
	m_data.push_back(0);
	return *this;
}

PalaceMessage& PalaceMessage::PutPStr(std::string_view s)
{
	m_data.push_back(static_cast<uint8_t>(s.size()));
	std::copy(s.begin(), s.end(), m_write);
	return *this;
}

PalaceMessage& PalaceMessage::PutData(const std::vector<uint8_t> &data)
{
	std::copy(data.begin(), data.end(), m_write);
	return *this;
}
