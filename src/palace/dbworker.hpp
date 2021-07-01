#ifndef _PALACE_DBWORKER_H
#define _PALACE_DBWORKER_H

#include <memory>

#include "../sqliteworker.hpp"

class Asset;
struct AssetSpec;

class PalaceDBWorker : public SQLiteWorker
{
public:
	PalaceDBWorker(const std::filesystem::path &dbPath);
	void Run();
private:
	Asset* GetAssetBySpec(const AssetSpec &spec);
	void WriteAsset(const std::weak_ptr<Asset> &asset);

	Point GetPoint(uint16_t index);
	void WritePoint(const Point &point);


};

#endif // _PALACE_DBWORKER_H
