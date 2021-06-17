#ifndef _PALACE_MESSAGE_H
#define _PALACE_MESSAGE_H

#include <iterator>
#include <string>
#include <string_view>
#include <vector>

struct PALACE_MSG_HEADER;

class PalaceMessage
{
public:
	PalaceMessage(std::vector<uint8_t> &incoming);
	PalaceMessage(uint32_t event, int32_t ref = 0);
	template <class T> PalaceMessage& Get(T &t);
	PalaceMessage& GetCStr(std::string &s);
	PalaceMessage& GetPStr(std::string &s);
	PalaceMessage& GetData(std::vector<uint8_t> &data, size_t length);
	template <class T> PalaceMessage& Put(T t);
	PalaceMessage& PutCStr(std::string_view s);
	PalaceMessage& PutPStr(std::string_view s);
	PalaceMessage& PutData(const std::vector<uint8_t> &data);
private:
	PALACE_MSG_HEADER m_header;
	std::vector<uint8_t> m_data;
	std::vector<uint8_t>::iterator m_read;
	std::back_insert_iterator<std::vector<uint8_t>> m_write;
};

#endif // _PALACE_MESSAGE_H
