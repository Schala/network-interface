#ifndef _PALACEASSET_H
#define _PALACEASSET_H

#include <memory>

#include "palacecommon.hpp"

class PalaceAsset : public std::enable_shared_from_this<PalaceAsset>
{
public:
	PalaceAssetSpec& GetSpec() const;
private:
	static const uint32_t CRCMagic = 0xD9216290;
	
	PalaceAssetType m_type;
	PalaceAssetSpec m_spec;
	PalaceAssetInfo m_info;
};

#endif // _PALACEASSET_H
