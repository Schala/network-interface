#ifndef _HLFILE_H
#define _HLFILE_H

#include <memory>
#include <string>

#include "../macros.h"
#include "hldatetime.hpp"

enum class HLFilePlatform : uint32_t
{
	Mac = CODE('AMAC'),
	Windows = CODE('MWIN')
};

enum class HLFileForkType : uint32_t
{
	Data = CODE('DATA'),
	Info = CODE('INFO'),
	MacResource = CODE('MACR') // obsolete
};

struct HLFlatFileForkHeader
{
	HLFileForkType type;
	uint32_t compression;
	uint8_t _reserved[4];
	uint32_t dataSize;

	HLFlatFileForkHeader(HLFileForkType type, uint32_t dataSize);
};

#include "../_3rdparty/pushpack1.h"

struct HLFlatFileInfoHeader
{
	HLFilePlatform platform;
	uint32_t type;
	uint32_t creator;
	uint32_t flags;
	uint32_t platformFlags;
	uint8_t _reserved[32];
	HLDateTime created;
	HLDateTime edited;
	uint16_t nameScript;
	uint16_t nameSize;
} PACK_STRUCT;

struct HLFlatFileHeader
{
	uint32_t format;
	uint16_t version;
	uint8_t _reserved[16];
	uint16_t numForks;
} PACK_STRUCT;

#include "../_3rdparty/poppack1.h"

class HLFlatFile : public std::enable_shared_from_this<HLFlatFile>
{
public:
	static const uint32_t Format = CODE('FILP');
	static const uint16_t Version = 1;
	static const uint16_t ForkCount = 2;
	static const HLFlatFileHeader Header;
private:
	HLFlatFileHeader m_header;
	HLFlatFileForkHeader m_infoHeader;
	HLFlatFileForkHeader m_dataHeader;
	HLFlatFileInfoHeader m_info;
	std::string m_name;
};

#endif // _HLFILE_H
