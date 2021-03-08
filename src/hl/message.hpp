#ifndef _HL_MESSAGE_H
#define _HL_MESSAGE_H

#include <any>
#include <array>
#include <boost/uuid/uuid.hpp>
#include <string>
#include <vector>

#include "../common.hpp"

namespace cmm
{
	namespace opcode
	{
		enum
		{
			error = 100,
			get_msgs,
			new_msg,
			old_post_news,
			server_msg,
			chat_send,
			chat_msg,
			login,
			send_instant_msg,
			show_agreement,
			disconnect_user,
			disconnect_msg,
			invite_new_chat,
			invite_to_chat,
			reject_chat_invite,
			join_chat,
			leave_chat,
			notify_chat_change_user,
			notify_chat_delete_user,
			notify_chat_subject,
			set_chat_subject,
			agreed,
			server_banner,
			get_file_name_list = 200,
			download_file = 202,
			upload_file,
			delete_file,
			new_folder,
			get_file_info,
			set_file_info,
			move_file,
			make_file_alias,
			download_fldr,
			download_info,
			download_banner,
			upload_fldr,
			get_user_name_list = 300,
			notify_change_user,
			notify_delete_user,
			get_client_info_text,
			set_client_user_info,
			new_user = 350,
			delete_user,
			get_user,
			set_user,
			user_access,
			user_broadcast,
			get_news_cat_name_list = 370,
			get_news_art_name_list,
			del_news_item = 380,
			new_news_fldr,
			new_news_cat,
			get_news_art_data = 400,
			post_news_art = 410,
			del_news_art,
			keep_connection_alive = 500
		};
	}

	struct message_header
	{
		uint8 flags;
		bool is_reply;
		uint16 opcode;
		uint32 id;
		uint32 error_code;
		uint32 total_size;
		uint32 chunk_size;
	};

	namespace param
	{
		enum
		{
			error_text = 100,
			data,
			user_name,
			user_id,
			user_icon_id,
			user_login,
			user_password,
			ref_num,
			transfer_size,
			chat_options,
			user_access,
			user_alias,
			user_flags,
			options,
			chat_id,
			chat_subject,
			waiting_count,
			server_agreement = 150,
			server_banner,
			server_banner_type,
			server_banner_url,
			no_server_agreement,
			vers = 160,
			community_banner_id,
			server_name,
			file_name_with_info = 200,
			file_name,
			file_path,
			file_resume_data,
			file_xfer_options,
			file_type_string,
			file_creator_string,
			file_size,
			file_create_date,
			file_modify_date,
			file_comment,
			file_new_name,
			file_new_path,
			file_type,
			quoting_msg,
			automatic_response,
			fldr_item_count = 220,
			user_name_with_info = 300,
			news_cat_guid = 319,
			news_cat_list_data,
			news_art_list_data,
			news_cat_name,
			news_cat_list_data15,
			news_path = 325,
			news_art_id,
			news_art_data_flav,
			news_art_title,
			news_art_poster,
			news_art_date,
			news_art_prev_art,
			news_art_next_art,
			news_art_data,
			news_art_flags,
			news_art_parent_art,
			news_art_1st_child_art,
			news_art_recurse_del
		};
	}

	struct field_header
	{
		uint16 id;
		uint32 size;
	};

	struct field
	{
		field_header header;
		std::any data;

		sizeint size() const;
	};

	struct message
	{
		message_header header;
		std::vector<field> fields;

		sizeint size() const
		{
			sizeint result = 22;
			for (sizeint i = 0; i < fields.size(); i++)
				result += fields[i].size() + 6;
			return result;
		}
	};

	typedef std::array<char, 4> str4;

	struct file_name_with_info_header
	{
		str4 type;
		str4 creator;
		uint32 size;
		uint32 _reserved;
		uint16 name_script;
	};

	struct file_name_with_info
	{
		file_name_with_info_header header;
		std::string name;
	};

	struct file_resume_data_header
	{
		str4 format;
		uint16 version;
		char _reserved[34];
		uint16 fork_count;
	};

	struct file_fork_info
	{
		str4 fork;
		uint32 size;
		uint32 _reserved0;
		uint32 _reserved1;
	};

	struct file_resume_data
	{
		file_resume_data_header header;
		std::vector<file_fork_info> fork_info;
	};

	struct date
	{
		uint16 year;
		uint16 milliseconds;
		uint32 seconds;
	};

	struct user_name_with_info_header
	{
		uint16 id;
		uint16 icon;
		uint16 flags;
	};

	struct user_name_with_info
	{
		user_name_with_info_header header;
		std::string name;
	};

	struct news_category_list_data
	{
		uint8 type;
		std::string name;
	};

	struct news_article_list_data_header
	{
		uint32 id;
		uint32 size;
	};

	struct news_article_header
	{
		uint32 id;
		date timestamp;
		uint32 parent_id;
		uint32 flags;
	};

	struct flavor
	{
		std::string mime;
		uint16 article_size;
	};

	struct news_article
	{
		news_article_header header;
		std::string title;
		std::string poster;
		std::vector<flavor> flavors;
	};

	struct news_article_list_data
	{
		news_article_list_data_header header;
		std::string name;
		std::string description;
		std::vector<news_article> articles;
	};
}

#endif // _HL_MESSAGE_H
