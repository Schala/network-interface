#include "account.hpp"

void CarrachoAccount::PasswordCrypt(std::string &s)
{
	for (int i = 0, b = 0; i < s.size(); i++, b++)
	{
		if (b == 0)
		{
			s[i] ^= 128;
			s[i] ^= 8;
		}
		else
		{
			if (b == 1)
			{
				s[i] ^= 4;
				s[i] ^= 64;
			}
			else
			{
				if (b == 2)
				{
					s[i] ^= 16;
					s[i] ^= 2;
				}
			}
		}

		if (b > 2) b = 0;
	}
}
