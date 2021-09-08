#ifndef _HL_ACCOUNT_H
#define _HL_ACCOUNT_H

#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "../netset.hpp"
#include "hlcommon.hpp"
#include "hluseraccess.hpp"

class HLAccount : public std::enable_shared_from_this<HLAccount>
{
public:
	static const std::shared_ptr<HLAccount> Null;

	HLAccount() = default;
	std::string& GetLogin();
	std::optional<ByteString>& GetPassword();
	HLUserAccess GetAccess() const;
	bool DontShowAgreement() const;
private:
	std::string m_name;
	std::string m_login;
	std::optional<ByteString> m_password;
	HLUserAccess m_access;
	uint16_t m_icon;
	uint16_t m_color;
};

typedef std::shared_ptr<HLAccount> HLAccountPtr;
typedef NetSet<HLAccountPtr> HLAccountSet;
typedef std::weak_ptr<HLAccount> HLAccountRef;

#endif // _HL_ACCOUNT_H
