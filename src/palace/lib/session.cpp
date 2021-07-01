#include "asset.hpp"
#include "codec.hpp"
#include "connection.hpp"
#include "message.hpp"
#include "protocol.hpp"
#include "session.hpp"

std::string_view PalaceSession::GetOSStr() const
{
	using namespace std::literals::string_view_literals;

	switch (m_os)
	{
		case LI_AUXFLAGS_MAC68K: return "68k Mac"sv;
		case LI_AUXFLAGS_MACPPC: return "PPC Mac"sv;
		case LI_AUXFLAGS_WIN16: return "16Bit Windows"sv;
		case LI_AUXFLAGS_WIN32: return "32Bit Windows"sv;
		case LI_AUXFLAGS_JAVA: return "Java"sv;
		default: return "Unknown"sv;
	}
}
