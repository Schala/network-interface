#ifndef _OWNED_MESSAGE_H
#define _OWNED_MESSAGE_H

#include <memory>

namespace cmm
{
	template <class T> class connection;
	
	/// Network message owned by a client
	template <class T> struct owned_message
	{
		/// The remote client connection that owns the message
		std::shared_ptr<connection<T>> remote = nullptr;

		/// Message data
		T data;
	};
}

#endif // _OWNED_MESSAGE_H
