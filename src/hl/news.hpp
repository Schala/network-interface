#ifndef _HL_NEWS_H
#define _HL_NEWS_H

#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class Article : public std::enable_shared_from_this<Article>
{
private:
	std::chrono::time_point m_time;
	std::weak_ptr<Article> m_prev;
	std::weak_ptr<Article> m_next;
	std::weak_ptr<Article> m_parent;
	std::string m_mime;
	std::string m_poster;
	std::string m_title;
	std::vector<std::shared_ptr<Article>> m_kids;
	std::vector<uint8_t> m_data;
	uint16_t m_id;
};

class Category : public std::enable_shared_from_this<Category>
{
private:
	std::string m_name;
	std::vector<std::shared_ptr<Article>> m_articles;
	boost::uuids::uuid m_guid;
};

class Bundle : public std::enable_shared_from_this<Bundle>
{
private:
	std::string m_name;
	std::vector<std::shared_ptr<Category>> m_categories;
};

#endif // _HL_NEWS_H
