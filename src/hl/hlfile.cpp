#include "hlfile.hpp"

HLFlatFileHeader HLFlatFile::Header =
{
	HLFlatFile::Format,
	HLFlatFile::Version,
	{ 0, 0 },
	HLFlatFile::ForkCount
};

HLFlatFileForkHeader::HLFlatFileForkHeader(HLFileForkType type, uint32_t dataSize):
	type(type),
	compression(0),
	_reserved(0),
	dataSize(dataSize)
{
}
