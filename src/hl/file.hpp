#ifndef _HL_FILE_H
#define _HL_FILE_H

#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <openssl/md5.h>
#include <string>

typedef std::array<uint8_t, 16> HAVALChecksum;
typedef std::array<uint8_t, MD5_DIGEST_LENGTH> MD5Checksum;
typedef std::array<uint8_t, 20> SHA1Checksum

class HLFile : public std::enable_shared_from_this<HLFile>
{
public:
	HAVALChecksum& HAVAL();
	MD5Checksum& MD5();
	SHA1Checksum& SHA1();
private:
	std::string m_creator;
	std::string m_note;
	std::filesystem::path m_path;
	SHA1Checksum m_sha1;
	MD5Checksum m_md5;
	HAVALChecksum m_haval;
	std::filesystem::file_status m_status;
	std::filesystem::file_time_type m_created;
	std::filesystem::file_time_type m_modified;
	size_t m_size;
};

#endif // _HL_FILE_H
