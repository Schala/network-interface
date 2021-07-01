#ifndef _PALACE_ASSET_H
#define _PALACE_ASSET_H

#include <memory>
#include <vector>

struct AssetSpec;
struct PROP_FLAGS;
struct Str31;
class PalaceDBWorker;

class Asset : public std::enable_shared_from_this<Asset>
{
public:
	Asset& GetSpec(AssetSpec &spec) const;
	Asset& GetFlags(PROP_FLAGS &flags) const;
	Asset& GetName(Str31 &name) const;
	Asset& GetType(uint32_t &type) const;
	Asset& SetSpec(const AssetSpec &spec);
	Asset& SetFlags(const PROP_FLAGS &flags);
	Asset& SetName(const char *name);
	bool Load(PalaceDBWorker &dbWorker);
	bool Save(PalaceDBWorker &dbWorker) const;
private:
	static constexpr uint32_t MAGIC = 0xD9216290;

	Str31 m_name;
	std::vector<uint8_t> m_data;
	AssetSpec m_spec;
	PROP_FLAGS m_flags;
	uint32_t m_type;

	uint32_t GenCRC();
};

#endif // _PALACE_ASSET_H
