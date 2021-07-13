#ifndef _CARRACHO_ACCOUNT_H
#define _CARRACHO_ACCOUNT_H

#include <cstdint>
#include <memory>
#include <string>

class CarrachoAccount : public std::enable_shared_for_this<CarrachoAccount>
{
public:
	static void PasswordCrypt(std::string &s);
private:
	std::string m_password;
};

#endif // _CARRACHO_ACCOUNT_H
