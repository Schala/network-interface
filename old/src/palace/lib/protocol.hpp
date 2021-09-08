#ifndef _PALACE_PROTOCOL_H
#define _PALACE_PROTOCOL_H

#include <cstdint>

// message IDs
enum
{
	MSGID_PICTDEL = 0x46505371,
	MSGID_HTTPSERVER = 0x48545450,
	MSGID_NOOP = 0x4E4F4F50,
	MSGID_ASSETNEW = 0x61417374,
	MSGID_AUTHENTICATE = 0x61757468,
	MSGID_AUTHRESPONSE = 0x61757472,
	MSGID_BLOWTHRU = 0x626C6F77,
	MSGID_LOGOFF = 0x62796520,
	MSGID_INITCONNECTION = 0x634C6F67,
	MSGID_SPOTMOVE = 0x636F4C73,
	MSGID_PROPDEL = 0x64507270,
	MSGID_SERVERDOWN = 0x646F776E,
	MSGID_DRAW = 0x64726177,
	MSGID_DISPLAYURL = 0x6475726C,
	MSGID_ROOMDESCEND = 0x656E6472,
	MSGID_USEREXIT = 0x65707273,
	MSGID_FILENOTFND = 0x666E6665,
	MSGID_GMSG = 0x676D7367,
	MSGID_SERVERUP = 0x696E6974,
	MSGID_KILLUSER = 0x6B696C6C,
	MSGID_DOORLOCK = 0x6C6F636B,
	MSGID_USERLOG = 0x6C6F6720,
	MSGID_PROPMOVE = 0x6D507270,
	MSGID_PICTNEW = 0x6E506374,
	MSGID_PROPNEW = 0x6E507270,
	MSGID_ROOMNEW = 0x6E526F6D,
	MSGID_ROOMGOTO = 0x6E617652,
	MSGID_USERNEW = 0x6E707273,
	MSGID_SPOTDEL = 0x6F705364,
	MSGID_SPOTNEW = 0x6F70536E,
	MSGID_SPOTSETDESC = 0x6F705373,
	MSGID_PICTMOVE = 0x704C6F63,
	MSGID_PING = 0x70696E67,
	MSGID_PONG = 0x706F6E67,
	MSGID_TROPSER = 0x70736572,
	MSGID_ASSETQUERY = 0x71417374,
	MSGID_FILEQUERY = 0x7146696C,
	MSGID_ASSETREGI = 0x72417374,
	MSGID_LISTOFALLROOMS = 0x724C7374,
	MSGID_LOGON = 0x72656769,
	MSGID_ALTLOGONREPLY = 0x72657032,
	MSGID_RESPORT = 0x72657370,
	MSGID_RMSG = 0x726D7367,
	MSGID_ROOMDESC = 0x726F6F6D,
	MSGID_USERLIST = 0x72707273,
	MSGID_DIYIT = 0x72796974,
	MSGID_ASSETSEND = 0x73417374,
	MSGID_NAVERROR = 0x73457272,
	MSGID_FILESEND = 0x7348696C,
	MSGID_EXTENDEDINFO = 0x73496E66,
	MSGID_PICTSETDESC = 0x73506374,
	MSGID_PROPSETDESC = 0x73507270,
	MSGID_ROOMSETDESC = 0x73526F6D,
	MSGID_SPOTSTATE = 0x73537461,
	MSGID_SERVERINFO = 0x73696E66,
	MSGID_SMSG = 0x736D7367,
	MSGID_SUPERUSER = 0x73757372,
	MSGID_TALK = 0x74616C6B,
	MSGID_TIMYID = 0x74696D79,
	MSGID_TIYID = 0x74697972,
	MSGID_USERMOVE = 0x754C6F63,
	MSGID_LISTOFALLUSERS = 0x754C7374,
	MSGID_USERSTATUS = 0x75537461,
	MSGID_DOORUNLOCK = 0x756E6C6F,
	MSGID_USERCOLOR = 0x75737243,
	MSGID_USERDESC,
	MSGID_USERFACE = 0x75737246,
	MSGID_USERNAME = 0x7573724E,
	MSGID_USERPROP = 0x75737250,
	MSGID_VERSION = 0x76657273,
	MSGID_WMSG = 0x776D7367,
	MSGID_USERENTER = 0x77707273,
	MSGID_XTALK = 0x78746C6B,
	MSGID_XWHISPER = 0x78776973,
};

enum
{
	RT_IUSR = 0x49557372,
	RT_PROP = 0x50726F70,
	RT_USER = 0x55736572
};

struct Str31
{
	uint8_t size;
	char text[31];

	void Set(const char *newText);
	void Set(const Str31 &other);
};

struct Str63
{
	uint8_t size;
	char text[63];

	void Set(const char *newText);
	void Set(const Str63 &other);
};

struct Point
{
	int16_t v;
	int16_t h;
};

struct AssetSpec
{
	int32_t id;
	uint32_t crc;
};

struct PALACE_MSG_HEADER
{
	uint32_t event;
	uint32_t size;
	int32_t ref;
};

struct AssetQuery
{
	uint32_t type;
	AssetSpec spec;
};

struct PROP_FLAGS
{
	uint32_t
		head : 1,
		ghost : 1,
		rare : 1,
		animate : 1,
		bounce : 1,
		fmt20Bit : 1,
		_reserved0 : 1,
		fmt32Bit : 1,
		fmtS20Bit : 1,
		png : 1,
		_reserved1 : 21;
};

struct AssetDescriptor
{
	PROP_FLAGS flags;
	uint32_t size;
	Str31 name;
};

struct ASSET_SEND_HEADER
{
	uint32_t type;
	AssetSpec spec;
	uint32_t blockSize;
	uint32_t blockOffs;
	uint16_t blockNum;
	uint16_t numBlocks;
	AssetDescriptor desc;
};

struct BLOWTHRU_TO_SERVER_HEADER
{
	uint32_t flags;
	uint32_t numUsers;
};

struct DoorLock
{
	int16_t roomID;
	int16_t doorID;
};

enum
{
	DRAW_PATH = 0,
	DRAW_SHAPE,
	DRAW_TEXT,
	DRAW_DETONATE,
	DRAW_DELETE,
	DRAW_ELLIPSE
};

struct LLRec
{
	uint16_t nextOffs;
	uint16_t reserved;
};

struct DRAW_HEADER
{
	LLRec link;
	uint16_t cmd;
	uint16_t cmdSize;
	uint16_t dataOffs;
};

enum
{
	SI_INF_AURL = 0x4155524C,
	SI_ERR_AUTH = 0x41555448,
	SI_INF_FLAG = 0x464C4147,
	SI_INF_HURL = 0x4855524C,
	SI_EXT_NAME = 0x4E414D45,
	SI_INF_NAME = SI_EXT_NAME,
	SI_EXT_NUM_USERS = 0x4E555352,
	SI_EXT_PASS = 0x50415353,
	SI_EXT_TYPE = 0x54595045,
	SI_INF_TYPE = SI_EXT_TYPE,
	SI_ERR_UNKN = 0x554E4B4E,
	SI_INF_VERS = 0x56455253
};

struct EXT_INFO_HEADER
{
	int32_t id;
	uint32_t size;
};

struct EXT_INFO_REQ_FLAGS
{
	uint32_t
		avatarURL : 1,
		serverVersion : 1,
		serverType : 1,
		serverFlags : 1,
		numUsers : 1,
		serverName : 1,
		httpURL : 1,
		_reserved : 25;
};

struct EXT_INFO_FLAGS_FLAGS
{
	uint16_t
		directPlay : 1,
		closedServer : 1,
		guestsAreMembers : 1,
		unused1 : 1,
		instantPalace : 1,
		palacePresents : 1,
		_reserved : 10;
};

enum
{
	PLAT_MAC = 0,
	PLAT_WIN95,
	PLAT_WINNT,
	PLAT_UNIX
};

struct EXT_INFO_FLAGS
{
	EXT_INFO_FLAGS_FLAGS flags;
	uint32_t capacity;
	uint8_t platform;	
};

struct FileDescriptor
{
	uint16_t numBlocks;
	uint32_t size;
	Str63 name;
};

struct FILE_SEND_HEADER
{
	int32_t transactionID;
	uint32_t blockSize;
	uint16_t blockNum;
	FileDescriptor desc;
};

struct ROOM_FLAGS16
{
	uint16_t
		authorLocked : 1,
		isPrivate : 1,
		noPainting : 1,
		closed : 1,
		cyborgFreeZone : 1,
		hidden : 1,
		noGuests : 1,
		wizardsOnly : 1,
		dropZone : 1,
		noLooseProps : 1,
		_reserved : 6;
};

struct ROOM_FLAGS32
{
	uint32_t
		authorLocked : 1,
		isPrivate : 1,
		noPainting : 1,
		closed : 1,
		cyborgFreeZone : 1,
		hidden : 1,
		noGuests : 1,
		wizardsOnly : 1,
		dropZone : 1,
		noLooseProps : 1,
		_reserved : 22;
};

struct ROOM_LIST_REC_HEADER
{
	int32_t id;
	ROOM_FLAGS16 flags;
	uint16_t numUsers;
};

struct USER_FLAGS
{
	uint16_t
		superUser : 1,
		god : 1,
		kill : 1,
		guest : 1,
		banished : 1,
		penalized : 1,
		commError : 1,
		gag : 1,
		pin : 1,
		_reserved : 7;
};

struct USER_LIST_REC_HEADER
{
	int32_t id;
	USER_FLAGS flags;
	int16_t roomID;
};

enum
{
	LI_AUXFLAGS_UNKNOWN_MACH = 0,
	LI_AUXFLAGS_MAC68K,
	LI_AUXFLAGS_MACPPC,
	LI_AUXFLAGS_WIN16,
	LI_AUXFLAGS_WIN32,
	LI_AUXFLAGS_JAVA,
	LI_AUXFLAGS_OSMASK = 15
};

struct AUX_FLAGS
{
	uint32_t
		os : 4,
		_reserved : 27,
		authenticate : 1;
};

struct UL_CAPS
{
	unsigned
		palaceAssets : 1,
		ftpAssets : 1,
		httpAssets : 1,
		otherAssets : 1,
		palaceFiles : 1,
		ftpFiles : 1,
		httpFiles : 1,
		otherFiles : 1,
		extendPacket : 1,
		_reserved : 23;
};

struct DL_CAPS
{
	uint32_t
		palaceAssets : 1,
		ftpAssets : 1,
		httpAssets : 1,
		otherAssets : 1,
		palaceFiles : 1,
		ftpFiles : 1,
		httpFiles : 1,
		otherFiles : 1,
		httpServerFiles : 1,
		extendPacket : 1,
		_reserved : 22;
};

struct ENG_CAPS_2D
{
	uint32_t
		palace : 1,
		doubleByte : 1,
		_reserved : 30;
};

struct GFX_CAPS_2D
{
	uint32_t
		gif87 : 1,
		gif89a : 1,
		jpeg : 1,
		tiff : 1,
		targa : 1,
		bitmap : 1,
		pict : 1,
		_reserved : 25;
};

struct ENG_CAPS_3D
{
	uint32_t
		vrml1 : 1,
		vrml2 : 1,
		_reserved : 30;
};

struct AuxRegistrationRec
{
	uint32_t crc;
	uint32_t counter;
	Str31 name;
	Str31 password;
	AUX_FLAGS flags;
	uint32_t puidCounter;
	uint32_t puidCRC;
	uint32_t demoElapsed;
	uint32_t totalElapsed;
	uint32_t demoLimit;
	int16_t desiredRoom;
	char reserved[6];
	uint32_t reqProtocolVer;
	UL_CAPS ulCaps;
	DL_CAPS dlCaps;
	ENG_CAPS_2D eng2DCaps;
	GFX_CAPS_2D gfx2DCaps;
	ENG_CAPS_3D eng3DCaps;
};

enum
{
	SE_INTERNAL = 0,
	SE_ROOM_UNKNOWN,
	SE_ROOM_FULL,
	SE_ROOM_CLOSED,
	SE_CANT_AUTHOR,
	SE_PALACE_FULL
};

struct PictMove
{
	int16_t roomID;
	int16_t spotID;
	Point pos;
};

struct PropMove
{
	uint32_t propNum;
	Point pos;
};

struct PropNew
{
	AssetSpec spec;
	Point pos;
};

struct ROOM_HEADER
{
	ROOM_FLAGS32 flags;
	int32_t facesID;
	int16_t id;
	uint16_t nameOffs;
	uint16_t bgNameOffs;
	uint16_t artistNameOffs;
	uint16_t passwordOffs;
	uint16_t numSpots;
	uint16_t spotOffs;
	uint16_t numPics;
	uint16_t picOffs;
	uint16_t numDraws;
	uint16_t drawOffs;
	uint16_t numUsers;
	uint16_t numLProps;
	uint16_t lPropOffs;
	uint16_t reserved;
	uint16_t bufSize;
};

struct SCRIPT_EVENT_MASK
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
		macro9 : 1,
		_reserved : 7;
};

enum
{
	HS_NORMAL = 0,
	HS_DOOR,
	HS_SHUTABLE_DOOR,
	HS_LOCKABLE_DOOR,
	HS_BOLT,
	HS_NAV_AREA
};

enum
{
	HS_UNLOCK = 0,
	HS_LOCK
};

struct SPOT_FLAGS
{
	uint32_t
		draggable : 1,
		dontMoveHere : 1,
		invisible : 1,
		showName : 1,
		showFrame : 1,
		shadow : 1,
		fill : 1,
		_reserved : 25;
};

struct SPOT_HEADER
{
	SCRIPT_EVENT_MASK scriptEventMask;
	SPOT_FLAGS flags;
	uint32_t secureInfo;
	int32_t ref;
	Point pos;
	int16_t id;
	int16_t dest;
	uint16_t numPoints;
	uint16_t pointOffs;
	uint16_t type;
	uint16_t groupID;
	uint16_t numScripts;
	uint16_t scriptRecOffs;
	uint16_t state;
	uint16_t numStates;
	uint16_t stateRecOffs;
	uint16_t nameOffs;
	uint16_t scriptTextOffs;
	uint16_t alignReserved;
};

struct State
{
	int16_t picID;
	uint16_t reserved;
	Point pos;
};

struct PICTURE_HEADER
{
	int32_t ref;
	int16_t id;
	uint16_t nameOffs;
	uint16_t alpha;
	uint16_t reserved;
};

struct LProp
{
	LLRec link;
	AssetSpec spec;
	PROP_FLAGS flags;
	int32_t ref;
	Point pos;
};

enum
{
	K_UNKNOWN = 0,
	K_LOGGED_OFF,
	K_COMM_ERROR,
	K_FLOOD,
	K_KILLED_BY_PLAYER,
	K_SERVER_DOWN,
	K_UNRESPONSIVE,
	K_KILLED_BY_SYSOP,
	K_SERVER_FULL,
	K_INVALID_SERIAL_NUM,
	K_DUPLICATE_USER,
	K_DEATH_PENALTY_ACTIVE,
	K_BANISHED,
	K_BANISH_KILL,
	K_NO_GUESTS,
	K_DEMO_EXPIRED,
	K_VERBOSE
};

struct SERVER_PERMS
{
	uint32_t
		allowGuests : 1,
		allowCyborgs : 1,
		allowPainting : 1,
		allowCustomProps : 1,
		allowWizards : 1,
		wizardsMayKill : 1,
		wizardsMayAuthor : 1,
		playersMayKill : 1,
		cyborgsMayKill : 1,
		deathPenalty : 1,
		purgeInactiveProps : 1,
		killFlooders : 1,
		noSpoofing : 1,
		memberCreatedRooms : 1,
		_reserved : 18;
};

struct SERVER_OPTIONS
{
	uint32_t
		saveSessionKeys : 1,
		passwordSecurity : 1,
		chatLog : 1,
		noWhisper : 1,
		allowDemoMembers : 1,
		authenticate : 1,
		poundProtect : 1,
		sortOptions : 1,
		authTrackLogoff : 1,
		javaSecure : 1,
		_reserved : 22;
};

struct ServerInfo
{
	SERVER_PERMS perms;
	Str63 name;
	SERVER_OPTIONS opts;
	UL_CAPS ulCaps;
	DL_CAPS dlCaps;
};

struct SpotMove
{
	int16_t roomID;
	int16_t id;
	Point pos;
};

struct SpotState
{
	int16_t roomID;
	int16_t id;
	uint16_t state;
};

enum
{
	FACE_CLOSED = 0,
	FACE_SMILE,
	FACE_TILT_DOWN,
	FACE_TALK,
	FACE_WINK_LEFT,
	FACE_NORMAL,
	FACE_WINK_RIGHT,
	FACE_TILT_LEFT,
	FACE_TILT_UP,
	FACE_TILT_RIGHT,
	FACE_SAD,
	FACE_BLOTTO,
	FACE_ANGRY
};

struct USER_DESC_HEADER
{
	uint16_t face;
	uint16_t color;
	uint32_t numProps;
};

struct User
{
	int32_t id;
	Point roomPos;
	AssetSpec props[9];
	int16_t roomID;
	uint16_t face;
	uint16_t color;
	uint16_t awayFlag;
	uint16_t openToMsgs;
	uint16_t numProps;
	Str31 name;
};

#endif // _PALACE_PROTOCOL_H
