set (HL_SOURCES
	hlaccount.cpp
	hlaccount.hpp
	hlcommon.hpp
	#hldatetime.hpp
	#hlfile.cpp
	#hlfile.hpp
	#hlnews.hpp
	hlserver.cpp
	hlserver.hpp
	#hlservertrackersession.hpp
	hlsession.cpp
	hlsession.hpp
	hltransaction.cpp
	hltransaction.hpp
	hluseraccess.cpp
	hluseraccess.hpp
	hluserflags.cpp
	hluserflags.hpp
	hluserinfo.cpp
	hluserinfo.hpp
	hlutils.hpp
)

add_executable (hlserver ${HL_SOURCES})
add_dependencies (hlserver cmmnet_core haval)
target_link_libraries (hlserver cmmnet_core haval ${OPENSSL_CRYPTO_LIBRARIES} ${SQLite3_LIBRARIES})
target_include_directories (hlserver PRIVATE ${Boost_INCLUDE_DIRS})

if (WIN32)
	target_link_libraries (hlserver wsock32 ws2_32)
endif ()
