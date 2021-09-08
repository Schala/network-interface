#ifndef _PALACE_SESSION_H
#define _PALACE_SESSION_H

#include <array>
#include <memory>
#include <string_view>

class PalaceConnection;
class PalaceMessage;
class PalaceCodec;
class Asset;
struct Str31;
struct Point;
struct UL_CAPS;
struct DL_CAPS;
struct ENG_CAPS_2D;
struct ENG_CAPS_3D;
struct GFX_CAPS_2D;
struct USER_FLAGS;

class PalaceSession : public std::enable_shared_from_this<PalaceSession>
{
public:
	std::string_view GetOSStr() const;
	uint32_t GetID() const;
private:
	std::shared_ptr<PalaceConnection> m_connection;
	Str31 m_name;
	Str31 m_password;
	std::array<std::weak_ptr<Asset>, 9> m_props;
	std::array<char, 6> m_vendor;
	Point m_pos;
	UL_CAPS m_ulCaps;
	DL_CAPS m_dlCaps;
	ENG_CAPS_2D m_engCaps2D;
	ENG_CAPS_3D m_engCaps3D;
	GFX_CAPS_2D m_gfxCaps2D;
	USER_FLAGS m_flags;
	uint32_t m_id;
	uint8_t m_os;
};

#endif // _PALACE_SESSION_H
