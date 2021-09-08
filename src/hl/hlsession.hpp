#ifndef _HL_SESSION_H
#define _HL_SESSION_H

#include <string>
#include <vector>

#include "../session.hpp"
#include "hlaccount.hpp"
#include "hltransaction.hpp"
#include "hluserinfo.hpp"

// Encapsulates the I/O functionality of the Hotline protocol between a client and server
class HLSession : public SessionBase<HLTransaction, boost::asio::ip::tcp>
{
public:
	HLSession(uint16_t id, SessionOwner owner, boost::asio::ip::tcp::socket socket, boost::asio::io_context &ctx,
		NetQueue<PacketType> &inQueue);
	~HLSession();

	// Sets up read and write operations
	void Start() override;

	// Sends a transaction to the remote endpoint, telling it to relay to all users.
	// This is usually a broadcasted message by the client.
	void SendAll(const HLTransaction &msg, bool ignoreSelf = true);

	// Disconnect from the remote endpoint.
	void Disconnect();

	// Are we connected to the remote endpoint?
	bool IsConnected() const override;

	// Returns the login time as a formatted string
	//std::string LoginTimeAsString() const;

	// Returns the idle (since last ping) time as a formatted string
	//std::string IdleTimeAsString() const;

	// Convenience function to cast base class shared_from_this()
	std::shared_ptr<HLSession> GetSharedPtr() const;

	// Increments and returns a copy of the session's last transaction ID
	uint32_t GetNewTransactionID();

	// Gets the current transaction ID, used by replies
	uint32_t GetCurrentTransactionID() const;

	// Returns the user's ID
	uint16_t GetUserID() const;

	// Sets the client version
	void SetVersion(uint16_t version);

	// Gets client version
	uint16_t GetVersion() const;

	// Validates and assigns an account pointer to the session
	bool ValidateLogin(const HLAccountSet &accounts, const std::string &login,
		const ByteString &password);
	
	// Gets a pointer to the account associated with the session
	HLAccountPtr GetAccount() const;

	// Sets the user's name (alias) and updates the data in the cached info header
	void SetName(const std::string &name);

	// Sets the user's icon ID
	void SetIconID(uint16_t id);

	// Sets the user's message flags
	void SetMessageFlags(HLMessageFlags flags);

	// Sets the user's auto reply when AFK
	void SetAutoReply(const std::string &message);

	// Convenience function calling GetAccess on account pointer
	HLUserAccess GetAccess() const;

	// Get user info
	HLUserInfo& GetUserInfo() const;
private:
	boost::asio::ip::tcp::socket m_sock;
	HLAccountRef m_account;
	std::optional<std::string> m_autoReply;
	ByteString m_sessKey;
	ByteString m_gifIcon;
	std::chrono::system_clock::time_point m_loginTime;
	HLUserInfo m_info;
	uint32_t m_lastTransID;
	uint16_t m_color;
	uint16_t m_version;
	HLMessageFlags m_msgFlags;
	HLCipher m_cipher;
	HLMACAlgorithm m_mac;
	HLCompression m_cmp;

	// Routinely called on a worker thread to read data from the remote endpoint.
	boost::asio::awaitable<void> Read();

	// Routinely called on a worker thread to write data to the remote endpoint.
	boost::asio::awaitable<void> Write();

	void OnError(const std::error_code &ec) override;
	//void OnDisconnect() override;
	void OnException(const std::string &what) override;
};

typedef std::shared_ptr<HLSession> HLSessionPtr;

#endif // _HL_SESSION_H
