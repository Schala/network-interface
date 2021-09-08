#ifndef _HL_NEWS_H
#define _HL_NEWS_H

#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <string>
#include <vector>

#include "hldatetime.hpp"

class HLNewsArticle
{
private:
	std::string m_title;
	std::string m_poster;
	std::string m_flavor;
	std::vector<uint8_t> m_data;
	HLDateTime m_datetime;
};

class HLNewsCategory
{
private:
	std::string m_name;
	boost::uuids::uuid m_guid;
	std::vector<HLNewsArticle> m_articles;
};

#endif // _HL_NEWS_H
