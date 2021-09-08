#ifndef _HL_TRANSACTION_H
#define _HL_TRANSACTION_H

#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <istream>
#include <optional>
#include <ostream>
#include <string>
#include <variant>

#include "hlcommon.hpp"
//#include "hldatetime.hpp"
#include "hluseraccess.hpp"
#include "hluserinfo.hpp"

// Transaction operation type
enum class HLOpcode : uint16_t
{
	Reply = 0,
	Error = 100,
	MessagesGet,
	MessageNew,
	NewsPostFlat,
	ServerMessage,
	ChatSend,
	ChatMessage,
	Login,
	PrivateMessageSend,
	AgreementShow,
	UserDisconnect,
	DisconnectMessage,
	NewChatInvite,
	ChatInvite,
	ChatInviteReject,
	ChatJoin,
	ChatLeave,
	ChatNotifyUserChange,
	ChatNotifyUserDelete,
	ChatTopicNotify,
	ChatTopicSet,
	Agreed,
	ServerBanner, // not implemented due to security flaws
	UserIconSet,
	UserAliasSet,
	UserFakeAdmin,
	UserAway,
	ServerCrazy,
	DownloadBlock,
	UserVisibility,
	AdminInspector,
	StandardMessage,
	NewsArticleEdit,
	FileNameListGet = 200,
	FileDownload = 202,
	FileUpload,
	FileDelete,
	FolderNew,
	FileInfoGet,
	FileInfoSet,
	FileMove,
	FileAliasNew,
	FolderDownload,
	DownloadInfo,
	DownloadBanner, // not implemented due to security flaws
	FolderUpload,
	UserNameListGet = 300,
	UserNotifyChange,
	UserNotifyDelete,
	UserInfoTextGet,
	UserNew = 350,
	UserDelete,
	UserGet,
	UserSet,
	UserAccess,
	UserBroadcast,
	NewsCategoryNameListGet = 370,
	NewsArticleNameListGet,
	NewsItemDelete = 380,
	NewsFolderNew,
	NewsCategoryNew,
	NewsArticleDataGet = 400,
	NewsArticlePost = 410,
	NewsArticleDelete,
	Ping = 500,
	UserIconList = 1861,
	UserIconClientSet,
	UserIconGet2,
	UserIconServerSet,
	LinkLogin = 2048,
	LinkJoin,
	LinkLeave,
	LinkPacket,
	NewsUnformattedGet = 2149,
	UserInfoUnformattedGet = 2160,
	AccountEditSelf = 2304,
	PermissionList,
	FileHash = 3808
};

// Parameter type, determines the kind of data associated with the parameter
enum class HLParamID : uint16_t
{
	Error = 100,
	Data,
	UserName,
	UserID,
	UserIconID,
	UserLogin,
	UserPassword,
	Reference,
	TransferSize,
	ChatOptions,
	UserAccess,
	UserAlias,
	UserFlags,
	Options,
	ChatID,
	ChatTopic,
	WaitingCount,
	UserIconChange,
	UserAliasChange,
	UserFakeAdmin,
	UserAway,
	DownloadBlock,
	UserVisibility,
	AdminInspector,
	StandardMessage,
	ServerAgreement = 150,
	ServerBanner, // not implemented due to security flaws
	ServerBannerType, // not implemented due to security flaws
	ServerBannerURL, // not implemented due to security flaws
	ServerAgreementNone,
	Version = 160,
	BannerID, // not implemented due to security flaws, will always be 0 or ignored
	ServerName,
	FileInfo = 200,
	FileName,
	FilePath,
	FileResumeData,
	FileTransferOptions,
	FileTypeString,
	FileCreatorString,
	FileSize,
	FileCreateDate,
	FileEditDate,
	FileComment,
	FileNameNew,
	FilePathNew,
	FileType,
	MessageQuote,
	AutoReply,
	FolderItemCount = 220,
	UserInfo = 300,
	NewsCategoryGUID = 319,
	NewsCategoryListDataOld, // not implemented, obsolete
	NewsArticleListData,
	NewsCategoryName,
	NewsCategoryListData,
	NewsPath = 325,
	NewsArticleID,
	NewsArticleDataFlavor,
	NewsArticleTitle,
	NewsArticlePoster,
	NewsArticleDate,
	NewsArticlePrevious,
	NewsArticleNext,
	NewsArticleData,
	NewsArticleFlags,
	NewsArticleRoot,
	NewsArticle1stChild,
	NewsArticleRecursiveDelete,
	GIFIcon = 768,
	GIFList,
	Offset = 793,
	Limit,
	Count,
	NewsLimit = 800,
	Search = 1024,
	Color = 1280,
	Packet = 1536,
	Post = 2048,
	PostID,
	PermissionGroup = 2128,
	Permissions,
	IPAddress = 2304,
	SessionKey = 3587,
	MACAlgorithm,
	SessionID = 3687,
	MD5 = 3712,
	HAVAL,
	SHA1,
	MacCIcon = 3728, // obsolete?
	ChatAway = 3745,
	ServerCipherAlgorithm = 3777,
	ClientCipherAlgorithm,
	ServerCipherMode,
	ClientCipherMode,
	ServerCipherInitVector,
	ClientCipherInitVector,
	ServerChecksumAlgorithm,
	ClientChecksumAlgorithm,
	ServerCompressionAlgorithm,
	ClientCompressionAlgorithm
};

// Contains metadata about a transaction, which may or may not contain additional data
struct HLTransactionHeader
{
	uint8_t flags;
	bool isReply;
	HLOpcode opcode;
	uint32_t id;
	uint32_t error;
	uint32_t totalSize;
	uint32_t chunkSize;
};

// Sent by the client when the connection is initialised
struct HLClientHello
{
	uint32_t protocol;
	uint32_t subProtocol;
	uint32_t version;
};

// Sent to the client by the server following a HLClientHello from the client
struct HLServerHello
{
	uint32_t protocol;
	uint32_t error;
};

// Parameter metadata
struct HLParamHeader
{
	HLParamID type;
	uint16_t size;
};

// A container of possible values for parameter data
typedef std::variant<
	bool,
	uint16_t, // small integers
	uint32_t, // larger integers
	std::string, // strings
	boost::uuids::uuid, // news category GUID
	ByteString, // misc. binary
	HLUserAccess,
	//HLDateTime,
	HLSessionFlags,
	HLMessageFlags,
	HLUserInfo,
	Bytes16, // MD5, HAVAL
	Bytes20, // SHA1
	std::nullptr_t // data not known
> HLParamData;

// A parameter belonging to a transaction
class HLParameter
{
	friend std::ostream& operator<<(std::ostream &buf, const HLParameter &param);
public:
	// Outgoing
	HLParameter(HLParamID type, HLParamData &data);

	// Incoming
	HLParameter(HLParamHeader &header, std::istream &buf);

	// Get the ID from the header
	HLParamID GetID() const;

	// Get the size of the data from the header
	uint16_t GetSize() const;

	// Get the data itself
	const HLParamData& GetData() const;
private:
	HLParamHeader m_header;
	HLParamData m_data;
};

// A client<->server transaction
class HLTransaction
{
	friend std::ostream& operator<<(std::ostream &buf, const HLTransaction &trans);
public:
	// Write
	HLTransaction(HLOpcode opcode, uint32_t id, uint32_t error = 0);
	
	// Receive with no parameters
	HLTransaction(HLTransactionHeader &header);

	// Receive, parameters expected
	HLTransaction(HLTransactionHeader &header, std::istream &buf);

	// Are we replying to a previous transaction?
	bool IsReply() const;

	// Get the opcode from the header
	HLOpcode GetOpcode() const;

	// Get the total size in bytes from the header
	uint32_t GetTotalSize() const;

	// Get the number of parameters for this transaction
	uint16_t GetParamCount() const;

	// Provides array-like access to parameters
	const HLParameter& operator[](size_t index) const;

	// Adds a new parameter to the transaction
	void AddParam(HLParamID type, HLParamData &data);
private:
	HLTransactionHeader m_header;
	std::optional<std::vector<HLParameter>> m_params;

	// If little endian host, reverse the header fields' byte order
	void FixHeaderEndianness();
};

// Write transaction to output buffer
std::ostream& operator<<(std::ostream &buf, const HLParameter &param);
std::ostream& operator<<(std::ostream &buf, const HLTransaction &trans);

#endif // _HL_TRANSACTION_H
