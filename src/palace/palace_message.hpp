#ifndef _PALACE_MESSAGE_H
#define _PALACE_MESSAGE_H

#include <algorithm>
#include <cstring>

#include "../common.hpp"

namespace cmm
{
	namespace opcode
	{
		enum
		{
			pict_del = 0x46505371,
			http_server = 0x48545450,
			no_op = 0x4E4F4F50,
			asset_new = 0x61417374,
			authenticate = 0x61757468,
			auth_response = 0x61757472,
			blow_thru = 0x626C6F77,
			log_off = 0x62796520,
			init_connection = 0x634C6F67,
			spot_move = 0x636F4C73,
			prop_del = 0x64507270,
			server_down = 0x646F776E,
			draw = 0x64726177,
			display_url = 0x6475726C,
			room_desc_end = 0x656E6472,
			user_exit = 0x65707273,
			file_not_fnd = 0x666E6665,
			gmsg = 0x676D7367,
			server_up = 0x696E6974,
			kill_user = 0x6B696C6C,
			door_lock = 0x6C6F636B,
			user_log = 0x6C6F6720,
			prop_move = 0x6D507270,
			pict_new = 0x6E506374,
			prop_new = 0x6E507270,
			room_new = 0x6E526F6D,
			room_go_to = 0x6E617652,
			user_new = 0x6E707273,
			spot_del = 0x6F705364,
			spot_new = 0x6F70536E,
			spot_set_desc = 0x6F705373,
			pict_move = 0x704C6F63,
			ping = 0x70696E67,
			pong = 0x706F6E67,
			tropser = 0x70736572,
			asset_query = 0x71417374,
			file_query = 0x7146696C,
			asset_regi = 0x72417374,
			list_of_all_rooms = 0x724C7374,
			log_on = 0x72656769,
			alt_logon_reply = 0x72657032,
			resport = 0x72657370,
			rmsg = 0x726D7367,
			room_desc = 0x726F6F6D,
			user_list = 0x72707273,
			diyit = 0x72796974,
			asset_send = 0x73417374,
			nav_error = 0x73457272,
			file_send = 0x7348696C,
			extended_info = 0x73496E66,
			pict_set_desc = 0x73506374,
			prop_set_desc = 0x73507270,
			room_set_desc = 0x73526F6D,
			spot_state = 0x73537461,
			server_info = 0x73696E66,
			smsg = 0x736D7367,
			super_user = 0x73757372,
			talk = 0x74616C6B,
			timyid = 0x74696D79,
			tiyid = 0x74697972,
			user_move = 0x754C6F63,
			list_of_all_users = 0x754C7374,
			user_status = 0x75537461,
			door_unlock = 0x756E6C6F,
			user_color = 0x75737243,
			user_desc,
			user_face = 0x75737246,
			user_name = 0x7573724E,
			user_prop = 0x75737250,
			version = 0x76657273,
			wmsg = 0x776D7367,
			user_enter = 0x77707273,
			xtalk = 0x78746C6B,
			xwhisper = 0x78776973,
		};
	}

	struct message_header
	{
		uint32 event;
		uint32 size;
		int32 ref;
	};

	struct asset_spec
	{
		int32 id;
		uint32 crc;
	};

	template <sizeint N> struct strn
	{
		uint8 size;
		char chars[N];

		template <class String> strn(const String &data)
		{
			std::memset(chars, 0, N);
			size = static_cast<uint8>(data.size());
			std::copy(data.begin(), size > N ? data.begin() + N : data.end(), chars);
		}
	};

	typedef strn<31> str31;
	typedef strn<63> str63;

	struct point
	{
		int16 v;
		int16 h;
	};

	struct asset_query
	{
		int32 type;
		asset_spec spec;
	};

	struct asset_descriptor
	{
		uint32 flags;
		uint32 size;
		str31 name;
	};

	struct asset_send_header
	{
		int32 type;
		asset_spec spec;
		int32 block_size;
		int32 block_offs;
		int16 block_num;
		int16 nblocks;
		asset_descriptor desc;
	};

	struct door_lock
	{
		int16 room_id;
		int16 door_id;
	};

	struct llrec
	{
		int16 next_offs;
		int16 _reserved;
	};

	struct draw_header
	{
		llrec link;
		int16 cmd;
		uint16 cmd_size;
		int16 data_offs;
	};

	struct extended_info_header
	{
		int32 id;
		int32 size;
	};

	struct file_descriptor
	{
		uint16 nblocks;
		int32 size;
		str63 name;
	};

	struct file_send_header
	{
		int32 transaction_id;
		int32 block_size;
		int16 block_num;
		file_descriptor desc;
	};

	struct room_list_rec_header
	{
		int32 room_id;
		int16 flags;
		int16 nusers;
	};

	struct user_list_rec_header
	{
		int32 user_id;
		int16 flags;
		int16 room_id;
	};

	struct aux_registration
	{
		uint32 crc;
		uint32 counter;
		str31 user_name;
		str31 wiz_password;
		int32 aux_flags;
		uint32 puid_ctr;
		uint32 puid_crc;
		uint32 demo_elapsed;
		uint32 total_elapsed;
		uint32 demo_limit;
		int16 desired_room;
		char reserved[6];
		uint32 requested_protocol_version;
		uint32 upload_caps;
		uint32 download_caps;
		uint32 engine_2d_caps;
		uint32 graphics_2d_caps;
		uint32 engine_3d_caps;
	};

	struct pict_move
	{
		int16 room_id;
		int16 spot_id;
		point pos;
	};

	struct prop_move
	{
		int32 prop_num;
		point pos;
	};

	struct prop_new
	{
		asset_spec prop_spec;
		point pos;
	};

	struct room_header
	{
		int32 flags;
		int32 faces_id;
		int16 id;
		int16 name_offs;
		int16 pict_name_offs;
		int16 artist_name_offs;
		int16 password_offs;
		int16 nhotspots;
		int16 hotspot_offs;
		int16 npictures;
		int16 picture_offs;
		int16 ndraw_cmds;
		int16 draw_cmd_offs;
		int16 nusers;
		int16 nlprops;
		int16 lprop_offs;
		int16 _reserved;
		int16 buf_size;
	};

	struct hotspot
	{
		int32 script_event_mask;
		int32 flags;
		int32 _secure_info;
		int32 ref_con;
		point loc;
		int16 id;
		int16 dest;
		int16 npoints;
		int16 points_offs;
		int16 type;
		int16 _group_id;
		int16 nscripts;
		int16 script_offs;
		int16 state;
		int16 nstates;
		int16 state_offs;
		int16 name_offs;
		int16 script_text_offs;
		int16 _align_reserved;
	};

	struct state_rec
	{
		int16 pict_id;
		int16 _reserved;
		point pic_loc;
	};

	struct picture_rec
	{
		int32 ref_con;
		int16 id;
		int16 name_offs;
		int16 trans_color;
		int16 _reserved;
	};

	struct lprop_rec
	{
		llrec link;
		asset_spec prop_spec;
		int32 flags;
		int32 ref_con;
		point loc;
	};

	struct server_info
	{
		int32 permissions;
		str63 name;
		uint32 options;
		uint32 upload_caps;
		uint32 download_caps;
	};

	struct spot_move
	{
		int16 room_id;
		int16 id;
		point pos;
	};

	struct spot_state
	{
		int16 room_id;
		int16 spot_id;
		int16 state;
	};

	struct user_desc_header
	{
		int16 face_num;
		int16 color_num;
		int32 nprops;
	};

	struct user_rec
	{
		int32 id;
		point room_pos;
		asset_spec prop_spec[9];
		int16 room_id;
		int16 face_num;
		int16 color_num;
		int16 _away_flag;
		int16 _open_to_msgs;
		int16 nprops;
		str31 name;
	};

	struct xwhisper_request_header
	{
		int32 target;
		int16 size;
	};
}

#endif // _PALACE_MESSAGE_H
