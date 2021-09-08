#ifndef _PALACECOMMON_H
#define _PALACECOMMON_H

#include <algorithm>
#include <array>
#include <vector>

#include "../macros.h"

struct PString31
{
	uint8_t size;
	char text[31];
};

struct PString63
{
	uint8_t size;
	char text[63];
};

// A simple 2D point
struct PalacePoint
{
	int16_t y;
	int16_t x;
};

// Predefined asset types
enum class PalaceAssetType : uint32_t
{
	InstantPalaceUserBase = CODE('IUsr'), // unused
	Prop = CODE('Prop'),
	UserBase = CODE('User') // unused
};

// Lightweight asset metadata
struct PalaceAssetSpec
{
	int32_t id;
	uint32_t crc;
};

struct PalaceAssetFlags
{
	uint32_t
		_reserved0 : 1,
		head : 1,
		ghost : 1,
		rare : 1,
		animate : 1,
		bounce : 1,
		format20bit : 1,
		_reserved1 : 1,
		format32Bit : 1,
		formatS20Bit : 1,
		png : 1;
};

// More asset metadata
struct PalaceAssetInfo
{
	PalaceAssetFlags flags;
	uint32_t size;
	PString31 name;
};

struct PalaceLinkedListNode
{
	uint16_t nextOffset;
	uint16_t _reserved;
};

enum class PalaceDrawCommand : uint16_t
{
	Path = 0, Shape, Text, Detonate, Delete, Ellipse
};

struct PalaceDrawNodeHeader
{
	PalaceLinkedListNode next;
	PalaceDrawCommand cmd;
	uint16_t size;
	uint16_t offset;
};

class PalaceDrawNode
{
private:
	PalaceDrawNodeHeader m_header;
	std::vector<uint8_t> m_data;
};

// Various server attributes
struct PalaceServerFlags
{
	uint32_t
		directPlay : 1,
		closed : 1,
		guestsAreMembers : 1, // obsolete, always on
		_reserved : 1,
		instantPalace : 1,
		palacePresents : 1; // obsolete, always off
};

// Indicates the platform the server software is running on
enum class PalaceServerPlatform : uint8_t
{
	Macintosh = 0,
	Windows9X, // obsolete
	WindowsNT,
	Unix
};

// File metadata
struct PalaceFileInfo
{
	uint16_t numBlocks;
	uint32_t size;
	PString63 name;
};

// Room attributes
struct PalaceRoomFlags
{
	uint16_t
		authorLocked : 1,
		isPrivate : 1,
		noPainting : 1,
		closed : 1,
		cyborgFreeZone : 1,
		hidden : 1,
		noGuests : 1, // obsolete, ignored on server
		adminsOnly : 1,
		dropZone : 1,
		noLooseProps : 1;
};

// User attributes
struct PalaceUserFlags
{
	uint16_t
		super : 1,
		admin : 1,
		kill : 1,
		guest : 1, // obsolete, ignored on server
		banished : 1, // shouldn't be used, redundant with kill, ignored by server
		penalized : 1, // obsolete, unused, ignored by server
		error : 1,
		gag : 1,
		pin : 1,
		hide : 1,
		rejectESP : 1,
		rejectPrivateMessages : 1,
		propGag : 1;
};

enum class PalaceFace : uint16_t
{
	Closed = 0,
	Smile,
	TiltDown,
	Talk,
	WinkLeft,
	Normal,
	WinkRight,
	TiltLeft,
	TiltUp,
	TiltRight,
	Sad,
	Blotto,
	Angry
};

enum class PalaceColor : uint16_t
{
	Red = 0,
	Orange,
	Gold,
	Yellow,
	YellowGreen,
	Green,
	Green2,
	GreenCyan,
	Cyan,
	CyanBlue,
	Blue,
	BlueViolet,
	Violet,
	Magenta,
	MagentaRose,
	Rose
};

struct PalaceUploadCapabilities
{
	uint32_t
		assetsPalace : 1,
		assetsFTP : 1,
		assetsHTTP : 1,
		assetsOther : 1,
		filesPalace : 1,
		filesFTP : 1,
		filesHTTP : 1,
		filesOther : 1,
		extend : 1;
};

struct PalaceDownloadCapabilities
{
	uint32_t
		assetsPalace : 1,
		assetsFTP : 1,
		assetsHTTP : 1,
		assetsOther : 1,
		filesPalace : 1,
		filesFTP : 1,
		filesHTTP : 1,
		filesOther : 1,
		filesHTTPServer : 1,
		extend : 1;
};

struct Palace2DEngineCapabilities
{
	uint32_t
		palace : 1,
		doubleByte : 1;
};

struct Palace2DGraphicsCapabilities
{
	uint32_t
		gif87 : 1,
		gif89a : 1,
		jpg : 1,
		tiff : 1,
		targa : 1,
		bmp : 1,
		pct : 1;
};

struct Palace3DEngineCapabilities
{
	uint32_t
		vrml1 : 1,
		vrml2 : 1;
};

enum class PalaceNavigationError : uint32_t
{
	Internal = 0,
	RoomUnknown,
	RoomFull,
	RoomClosed,
	CantAuthor,
	ServerFull
};

struct PalaceScriptEventFlags
{
	uint32_t
		select : 1,
		lock : 1,
		unlock : 1,
		hide : 1,
		show : 1,
		startup : 1,
		alarm : 1,
		custom : 1,
		inChat : 1,
		propChange : 1,
		enter : 1,
		leave : 1,
		outChat : 1,
		signOn : 1,
		signOff : 1,
		macro0 : 1,
		macro1 : 1,
		macro2 : 1,
		macro3 : 1,
		macro4 : 1,
		macro5 : 1,
		macro6 : 1,
		macro7 : 1,
		macro8 : 1,
		macro9 : 1;
};

struct PalaceSpotFlags
{
	uint16_t
		draggable : 1,
		dontMoveHere : 1,
		invisible : 1,
		showName : 1,
		drawFrame : 1,
		shadow : 1,
		fill : 1;
};

enum class PalaceSpotType : uint16_t
{
	Normal = 0,
	Door,
	ShutableDoor,
	LockableDoor,
	Bolt,
	NavigationArea
};

enum class PalaceSpotState : uint16_t
{
	Unlock = 0,
	Lock
};

struct PalaceState
{
	uint16_t imageID;
	uint16_t _reserved;
	PalacePoint location;
};

struct PalaceLooseProp
{
	PalaceLinkedListNode link;
	PalaceAssetSpec spec;
	PalaceAssetFlags flags;
	int32_t ref;
	PalacePoint location;
};

struct PalaceServerAccess
{
	uint32_t
		allowGuests : 1, // obsolete, always on
		allowCyborgs : 1,
		allowPainting : 1,
		allowCustomProps : 1,
		allowAdmins : 1,
		adminsMayKill : 1,
		adminsMayAuthor : 1,
		usersMayKill : 1,
		cyborgsMayKill : 1,
		deathPenalty : 1,
		purgeInactiveProps : 1,
		kickSpammers : 1,
		noSpoofing : 1,
		userCreatedRooms : 1;
};

struct PalaceServerOptions
{
	uint32_t
		saveSessionKeys : 1, // obsolete, unused
		passworded : 1,
		logChat : 1,
		noWhisper : 1,
		allowDemoUsers : 1, // obsolete, always on
		authenticate : 1,
		poundProtect : 1,
		sortOptions : 1,
		trackLogoff : 1,
		javaSecure : 1;
};

struct PalaceServerInfo
{
	PalaceServerAccess access;
	PString63 name;
	PalaceServerOptions options;
	PalaceUploadCapabilities ulCapabilities;
	PalaceDownloadCapabilities dlCapabilities;
};

#endif // _PALACECOMMON_H
