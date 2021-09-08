#ifndef _HLUSERACCESS_H
#define _HLUSERACCESS_H

#include <boost/predef.h>
#include <cstdint>
#include <istream>
#include <ostream>

class HLUserAccess
{
	friend std::ostream& operator<<(std::ostream &buf, HLUserAccess access);
public:
	HLUserAccess(uint64_t access);
	HLUserAccess(std::istream &buf);
	
	bool DontShowAgreement() const;

private:
	union
	{
		uint64_t m_opaque;

		struct
		{
			uint64_t
#if BOOST_ENDIAN_BIG_BYTE
				deleteFiles : 1,
				uploadFiles : 1,
				downloadFiles : 1,
				renameFiles : 1,
				moveFiles : 1,
				createFolders : 1,
				deleteFolders : 1,
				renameFolders : 1,

				moveFolders : 1,
				readChat : 1,
				sendChat : 1,
				createChats : 1,
				closeChats : 1,
				showInList : 1,
				createUsers : 1,
				deleteUsers : 1,

				openUsers : 1,
				editUsers : 1,
				editOwnPassword : 1,
				sendPrivateMessages : 1,
				readNewsArticles : 1,
				postNewsArticles : 1,
				kickUsers : 1,
				cantBeKicked : 1,

				getUserInfo : 1,
				uploadAnywhere : 1,
				anyName : 1,
				noAgreement : 1,
				setFileComments : 1,
				setFolderComments : 1,
				viewDropBoxes : 1,
				makeAliases : 1,

				broadcast : 1,
				deleteNewsArticles : 1,
				createNewsCategories : 1,
				deleteNewsCategories : 1,
				createNewsFolders : 1,
				deleteNewsFolders : 1,
				uploadFolders : 1,
				downloadFolders : 1,

				sendMessages : 1,
				fakeRed : 1,
				away : 1,
				changeName : 1,
				changeIcon : 1,
				speakBefore : 1,
				refuseChatInvites : 1,
				blockDownloads : 1,

				visibility : 1,
				viewInvisible : 1,
				flood : 1,
				viewOwnDropBox : 1,
				dontQueue : 1,
				adminInspector : 1,
				postBefore : 1;
#else
				renameFolders : 1,
				deleteFolders : 1,
				createFolders : 1,
				moveFiles : 1,
				renameFiles : 1,
				downloadFiles : 1,
				uploadFiles : 1,
				deleteFiles : 1,

				deleteUsers : 1,
				createUsers : 1,
				showInList : 1,
				closeChats : 1,
				createChats : 1,
				sendChat : 1,
				readChat : 1,
				moveFolders : 1,

				cantBeKicked : 1,
				kickUsers : 1,
				postNewsArticles : 1,
				readNewsArticles : 1,
				sendPrivateMessages : 1,
				editOwnPassword : 1,
				editUsers : 1,
				openUsers : 1,

				makeAliases : 1,
				viewDropBoxes : 1,
				setFolderComments : 1,
				setFileComments : 1,
				noAgreement : 1,
				anyName : 1,
				uploadAnywhere : 1,
				getUserInfo : 1,

				downloadFolders : 1,
				uploadFolders : 1,
				deleteNewsFolders : 1,
				createNewsFolders : 1,
				deleteNewsCategories : 1,
				createNewsCategories : 1,
				deleteNewsArticles : 1,
				broadcast : 1,

				blockDownloads : 1,
				refuseChatInvites : 1,
				speakBefore : 1,
				changeIcon : 1,
				changeName : 1,
				away : 1,
				fakeRed : 1,
				sendMessages : 1,

				postBefore : 1,
				adminInspector : 1,
				dontQueue : 1,
				viewOwnDropBox : 1,
				flood : 1,
				viewInvisible : 1,
				visibility : 1;
#endif // endianness
		} m_bits;
	};
};

std::ostream& operator<<(std::ostream &buf, HLUserAccess access);

#endif // _HLUSERACCESS_H
