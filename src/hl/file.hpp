#ifndef _HL_FILE_H
#define _HL_FILE_H

#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <openssl/md5.h>
#include <string>

class File : public std::enable_shared_from_this<File>
{
public:
	std::array<uint8_t, 16>& HAVAL();
	std::array<uint8_t, MD5_DIGEST_LENGTH>& MD5();
	std::array<uint8_t, 20>& SHA1();
private:
	std::string m_creator;
	std::string m_note;
	std::filesystem::path m_path;
	std::array<uint8_t, 20> m_sha1;
	std::array<uint8_t, MD5_DIGEST_LENGTH> m_md5;
	std::array<uint8_t, 16> m_haval;
	std::filesystem::file_status m_status;
	std::filesystem::file_time_type m_created;
	std::filesystem::file_time_type m_modified;
	uintmax_t m_size;
};

#endif // _HL_FILE_H
