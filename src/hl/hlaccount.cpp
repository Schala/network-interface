#include "hlaccount.hpp"

const std::shared_ptr<HLAccount> HLAccount::Null = std::make_shared<HLAccount>();

std::string& HLAccount::GetLogin()
{
	return m_login;
}

std::optional<ByteString>& HLAccount::GetPassword()
{
	return m_password;
}

HLUserAccess HLAccount::GetAccess() const
{
	return m_access;
}

bool HLAccount::DontShowAgreement() const
{
	return m_access.DontShowAgreement();
}
