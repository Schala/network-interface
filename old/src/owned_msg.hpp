#ifndef _OWNED_MESSAGE_H
#define _OWNED_MESSAGE_H

#include <memory>

template <class T> class Connection;

/// Network message owned by a client
template <class T> struct OwnedMsg
{
	/// The remote client connection that owns the message
	std::shared_ptr<Connection<T>> remote = nullptr;

	/// Message data
	T data;
};

#endif // _OWNED_MESSAGE_H
