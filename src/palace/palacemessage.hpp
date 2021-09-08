#ifndef _PALACEMESSAGE_H
#define _PALACEMESSAGE_H

#include <string>

#include "palacecommon.hpp"

enum class PalaceEvent : uint32_t
{
	ImageDelete = CODE('FPSq'),
	ServerHTTP = CODE('HTTP'),
	None = CODE('NOOP'),
	AssetNew = CODE('aAst'),
	Authenticate = CODE('auth'),
	AuthReply = CODE('autr'),
	BlowThru = CODE('blow'),
	LogOff = CODE('bye '),
	ConnectionInit = CODE('cLog'), // unused
	SpotMove = CODE('coLs'),
	PropDelete = CODE('dPrp'),
	ServerDown = CODE('down'),
	Draw = CODE('draw'),
	DisplayURL = CODE('durl'),
	RoomInfoEnd = CODE('endr'),
	UserExit = CODE('eprs'),
	FileNotFound = CODE('fnfe'),
	MessageGlobal = CODE('gmsg'),
	ServerUp = CODE('init'), // unused
	UserKill = CODE('kill'),
	DoorLock = CODE('lock'),
	UserLog = CODE('log '),
	PropMove = CODE('mPrp'),
	ImageNew = CODE('nPct'),
	PropNew = CODE('nPrp'),
	RoomNew = CODE('nRom'),
	RoomGoTo = CODE('navR'),
	UserNew = CODE('nprs'),
	SpotDelete = CODE('opSd'),
	SpotNew = CODE('opSn'),
	SpotSetInfo = CODE('opSs'),
	ImageMove = CODE('pLoc'),
	Ping = CODE('ping'),
	Pong = CODE('pong'),
	ResportReverse = CODE('pser'),
	AssetQuery = CODE('qAst'),
	FileQuery = CODE('qFil'),
	AssetRegister = CODE('rAst'),
	RoomList = CODE('rLst'),
	LogOn = CODE('regi'),
	AltLogonReply = CODE('rep2'),
	Resport = CODE('resp'),
	MessageRoom = CODE('rmsg'),
	RoomInfo = CODE('room'),
	RoomUserList = CODE('rprs'),
	IDAssignReverse = CODE('ryit'),
	AssetSend = CODE('sAst'),
	NavigationError = CODE('sErr'),
	FileSend = CODE('sFil'),
	ExtendedInfo = CODE('sInf'),
	ImageSetInfo = CODE('sPct'), // unused
	PropSetInfo = CODE('sPrp'), // unused
	RoomSetInfo = CODE('sRom'),
	SpotState = CODE('sSta'),
	ServerInfo = CODE('sinf'),
	MessageServer = CODE('smsg'),
	UserAdmin = CODE('susr'),
	Talk = CODE('talk'),
	IDAcknowledge = CODE('timy'), // unused
	IDAssign = CODE('tiyr'),
	UserMove = CODE('uLoc'),
	UserList = CODE('uLst'),
	UserFlags = CODE('uSta'),
	DoorUnlock = CODE('unlo'),
	UserColor = CODE('usrC'),
	UserInfo,
	UserFace = CODE('usrF'),
	UserName = CODE('usrN'),
	UserProp = CODE('usrP'),
	Version = CODE('vers'),
	Whisper = CODE('whis'),
	MessageWhisper = CODE('wmsg'),
	UserEnter = CODE('wprs'),
	TalkEncoded = CODE('xtlk'),
	WhisperEncoded = CODE('xwis')
};

struct PalaceMessageHeader
{
	PalaceEvent event;
	uint32_t size;
	int32_t ref;
};

struct PalaceAssetQuery
{
	PalaceAssetType type;
	PalaceAssetSpec spec;
};

struct PalaceAssetSendHeader
{
	PalaceAssetType type;
	PalaceAssetSpec spec;
	uint32_t blockSize;
	uint32_t blockOffset;
	uint16_t blockNum;
	uint16_t numBlocks;
	PalaceAssetInfo info;
};

struct PalaceBlowThruClientToServerHeader
{
	uint32_t flags;
	uint32_t numUsers;
};

struct PalaceDoorLock
{
	uint16_t roomID;
	uint16_t spotID;
};

struct PalaceExtendedInfoRequestFlags
{
	uint32_t
		avatarURL : 1,
		serverVersion : 1,
		serverType : 1,
		serverFlags : 1,
		numUsers : 1,
		serverName : 1,
		mediaURL : 1;
};

enum class PalaceExtendedInfoID : uint32_t
{
	AvatarURL = CODE('AURL'),
	AuthenticationNeeded = CODE('AUTH'),
	Flags = CODE('FLAG'),
	MediaURL = CODE('HURL'),
	Name = CODE('NAME'),
	UserCount = CODE('NUSR'),
	Password = CODE('PASS'),
	Type = CODE('TYPE'),
	Unknown = CODE('UNKN'),
	Version = CODE('VERS')
};

struct PalaceExtendedInfoHeader
{
	PalaceExtendedInfoID id;
	uint32_t size;
};

struct PalaceFileSendHeader
{
	uint32_t transactionID;
	uint32_t blockSize;
	uint16_t blockID;
	PalaceFileInfo info;
};

struct PalaceRoomListNodeHeader
{
	uint32_t id;
	PalaceRoomFlags flags;
	uint16_t numUsers;
};

struct PalaceUserListNodeHeader
{
	uint32_t id;
	PalaceUserFlags flags;
	uint16_t roomID;
};

// Indicates the platform the client software is running on
enum class PalaceClientPlatform : uint32_t
{
	Unknown = 0,
	Mac68K, // obsolete
	MacPPC, // obsolete
	Win16, // obsolete
	Win32, // deprecated
	Java
};

struct PalaceAuxFlags
{
	PalaceClientPlatform osMask : 4;
	uint32_t _reserved : 27;
	uint32_t authenticate : 1;
};

struct PalaceUserRegistration
{
	uint32_t crc; // obsolete, ignored on server
	uint32_t counter; // obsolete, ignored on server
	PString31 userName;
	PString31 password;
	PalaceAuxFlags flags;
	uint32_t puidCounter; // obsolete, ignored on server
	uint32_t puidCRC; // obsolete, ignored on server
	uint32_t demoElapsed; // obsolete, ignored on server
	uint32_t totalElapsed; // // obsolete, ignored on server
	uint32_t demoLimit; // obsolete, ignored on server
	uint16_t desiredRoom;
	std::array<char, 6> clientType;
	uint32_t requestedProtocolVersion;
	PalaceUploadCapabilities ulCapabilities;
	PalaceDownloadCapabilities dlCapabilities;
	Palace2DEngineCapabilities engine2DCapabilities;
	Palace2DGraphicsCapabilities graphics2DCapabilities;
	Palace3DEngineCapabilities engine3DCapabilities;
};

struct PalaceImageMove
{
	uint16_t roomID;
	uint16_t spotID;
	PalacePoint position;
};

struct PalacePropMove
{
	uint32_t id;
	PalacePoint position;
};

struct PalacePropNew
{
	PalaceAssetSpec spec;
	PalacePoint position;
};

struct PalaceRoomInfoHeader
{
	uint32_t flags; // typecast here
	uint32_t facesID;
	uint16_t id;
	uint16_t nameOffset;
	uint16_t bgNameOffset;
	uint16_t artistNameOffset;
	uint16_t passwordOffset;
	uint16_t numSpots;
	uint16_t spotsOffset;
	uint16_t numImages;
	uint16_t imagesOffset;
	uint16_t numDraws;
	uint16_t drawsOffset;
	uint16_t numUsers;
	uint16_t numLooseProps;
	uint16_t loosePropsOffset;
	uint16_t _reserved;
	uint16_t bufferSize;
};

struct PalaceSpotHeader
{
	PalaceScriptEventFlags events;
	PalaceSpotFlags flags;
	uint32_t secureInfo; // unused
	int32_t ref; // unused
	PalacePoint location;
	uint16_t id;
	uint16_t destination;
	uint16_t numPoints;
	uint16_t pointsOffset;
	PalaceSpotType type;
	uint16_t groupID; // unused
	uint16_t numScripts;
	uint16_t scriptsInfoOffset;
	PalaceSpotState state;
	uint16_t numStates;
	uint16_t statesOffset;
	uint16_t nameOffset;
	uint16_t scriptsOffset;
	uint16_t _reserved;
};

struct ImageHeader
{
	int32_t ref; // unused
	uint16_t id;
	uint16_t nameOffset;
	uint16_t alphaColor;
	uint16_t _reserved;
};

enum class PalaceServerDown : int32_t
{
	Unknown = 0,
	LoggedOff,
	CommunicationError,
	Spam,
	KickedByUser,
	ServerDown,
	Unresponsive,
	KickedByAdmin,
	ServerFull,
	InvalidSerialNumber, // obsolete, unused
	DuplicateUser,
	BanActive,
	Banished,
	BanishKill,
	NoGuests, // obsolete, unused
	DemoExpired, // obsolete, unused
	Verbose
};

struct PalaceSpotMove
{
	uint16_t roomID;
	uint16_t spotID;
	PalacePoint position;
};

struct PalaceSetSpotState
{
	uint16_t roomID;
	uint16_t spotID;
	PalaceSpotState state;
};

struct PalaceUserInfoHeader
{
	PalaceFace face;
	PalaceColor color;
	uint32_t numProps;
};

struct PalaceRoomUserNode
{
	uint32_t id;
	PalacePoint position;
	PalaceAssetSpec props[9];
	uint16_t roomID;
	PalaceFace face;
	PalaceColor color;
	uint16_t away; // unused
	uint16_t openToMessages; // unused
	uint16_t numProps;
	PString31 name;
};

struct PalaceWhisperRequestHeader
{
	uint32_t target;
	uint16_t size;
};

#include "../_3rdparty/pushpack1.h"

struct PalaceExtendedInfoFlags
{
	PalaceServerFlags flags;
	uint32_t capacity;
	PalaceServerPlatform platform;
} PACK_STRUCT;

#include "../_3rdparty/poppack1.h"

class PalaceFileSend
{
private:
	PalaceFileSendHeader m_header;
	std::vector<uint8_t> m_data;
};

class PalaceRoomListNode
{
private:
	PalaceRoomListNodeHeader m_header;
	std::string m_name;
};

class PalaceUserListNode
{
private:
	PalaceUserListNodeHeader m_header;
	std::string m_name;
};

class PalaceRoomInfo
{
private:
	PalaceRoomInfoHeader m_header;
	std::vector<uint8_t> m_body;
};

#endif // _PALACEMESSAGE_H
