#ifndef _HL_NEWS_H
#define _HL_NEWS_H

#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class HLNewsArticle : public std::enable_shared_from_this<HLNewsArticle>
{
private:
	std::chrono::time_point m_time;
	std::weak_ptr<HLNewsArticle> m_prev;
	std::weak_ptr<HLNewsArticle> m_next;
	std::weak_ptr<HLNewsArticle> m_parent;
	std::string m_mime;
	std::string m_poster;
	std::string m_title;
	std::vector<std::shared_ptr<HLNewsArticle>> m_kids;
	std::vector<uint8_t> m_data;
	uint16_t m_id;
};

class HLNewsCategory : public std::enable_shared_from_this<HLNewsCategory>
{
private:
	std::string m_name;
	std::vector<std::shared_ptr<HLNewsArticle>> m_articles;
	boost::uuids::uuid m_guid;
};

class HLNewsBundle : public std::enable_shared_from_this<HLNewsBundle>
{
private:
	std::string m_name;
	std::vector<std::shared_ptr<HLNewsCategory>> m_categories;
};

#endif // _HL_NEWS_H
