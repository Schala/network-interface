#ifndef _PALACE_CONNECTION_H
#define _PALACE_CONNECTION_H

#include <array>
#include <string_view>

#include "../../connection.hpp"

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

class PalaceConnection : public Connection<PalaceMessage>
{
public:
	std::string_view GetOSStr() const;
private:
	PalaceCodec m_codec;
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
	uint8_t m_os;
};

#endif // _PALACE_CONNECTION_H
