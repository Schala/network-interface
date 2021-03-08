#include <iostream>

#include "message.hpp"

cmm::sizeint cmm::field::size() const
{
	try
	{
		switch (header.id)
		{
			case cmm::param::error_text:
			case cmm::param::user_name:
			case cmm::param::user_login:
			case cmm::param::user_alias:
			case cmm::param::chat_subject:
			case cmm::param::server_agreement:
			case cmm::param::server_banner_url:
			case cmm::param::server_name:
			case cmm::param::file_name:
			case cmm::param::file_type_string:
			case cmm::param::file_creator_string:
			case cmm::param::file_comment:
			case cmm::param::file_new_name:
			case cmm::param::quoting_msg:
			case cmm::param::automatic_response:
			case cmm::param::news_cat_name:
			case cmm::param::news_art_data_flav:
			case cmm::param::news_art_title:
			case cmm::param::news_art_poster:
				return std::any_cast<std::string>(data).size();
			case cmm::param::data:
			case cmm::param::user_password:
			case cmm::param::server_banner:
			case cmm::param::news_art_data:
				return std::any_cast<std::vector<cmm::uint8>>(data).size();
			case cmm::param::user_id:
			case cmm::param::user_icon_id:
			case cmm::param::ref_num:
			case cmm::param::transfer_size:
			case cmm::param::chat_options:
			case cmm::param::user_flags:
			case cmm::param::options:
			case cmm::param::chat_id:
			case cmm::param::waiting_count:
			case cmm::param::server_banner_type:
			case cmm::param::no_server_agreement:
			case cmm::param::vers:
			case cmm::param::community_banner_id:
			case cmm::param::file_xfer_options:
			case cmm::param::fldr_item_count:
			case cmm::param::news_art_id:
			case cmm::param::news_art_prev_art:
			case cmm::param::news_art_next_art:
			case cmm::param::news_art_flags:
			case cmm::param::news_art_parent_art:
			case cmm::param::news_art_1st_child_art:
			case cmm::param::news_art_recurse_del:
				return 2;
			case cmm::param::file_size:
			case cmm::param::file_type:
				return 4;
			case cmm::param::user_access:
			case cmm::param::file_create_date:
			case cmm::param::file_modify_date:
			case cmm::param::news_art_date:
				return 8;
			// 2 extra bytes for name length
			case cmm::param::file_name_with_info:
				return 20 + std::any_cast<cmm::file_name_with_info>(data).name.size();
			case cmm::param::file_resume_data:
				return 42 + std::any_cast<cmm::file_resume_data>(data).fork_info.size() * 16;
			// 2 extra bytes for name length
			case cmm::param::user_name_with_info:
				return 8 + std::any_cast<cmm::user_name_with_info>(data).name.size();
			case cmm::param::news_cat_guid:
				return 16;
			default:
				return 0;
		}
	}
	catch (std::bad_any_cast&)
	{
		std::cerr << "Malformed contents in field with ID " << header.id << std::endl;
		return 0;
	}
}
