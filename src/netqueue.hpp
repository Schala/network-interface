#ifndef _NETQUEUE_H
#define _NETQUEUE_H

#include <deque>
#include <mutex>

// Thread-safe queue using a lockable mutex
template <class T> class NetQueue
{
public:
	NetQueue() = default;

	// Queues cannot be copied
	NetQueue(const NetQueue<T>&) = delete;

	~NetQueue();

	// Returns the front element of the queue
	const T& Front();

	// Pushes an element to the end of the queue
	void Push(const T &item);

	// Pushes an element to the beginning of the queue, useful for redos
	void PushFront(const T &item);

	// Removes and returns the front element from the queue
	T Pop();

	// Is the queue empty?
	bool IsEmpty();

	// Clears the queue of all elements
	void Clear();
private:
	std::mutex m_mtx;
	std::deque<T> m_data;
};

template <class T>
const T& NetQueue<T>::Front()
{
	std::scoped_lock lock(m_mtx);
	return m_data.front();
}

template <class T>
void NetQueue<T>::Push(const T &item)
{
	std::scoped_lock lock(m_mtx);
	m_data.push_back(item);
}

template <class T>
void NetQueue<T>::PushFront(const T &item)
{
	std::scoped_lock lock(m_mtx);
	m_data.push_front(item);
}

template <class T>
T NetQueue<T>::Pop()
{
	std::scoped_lock lock(m_mtx);
	return m_data.pop_front();
}

template <class T>
bool NetQueue<T>::IsEmpty()
{
	std::scoped_lock lock(m_mtx);
	return m_data.empty();
}

template <class T>
void NetQueue<T>::Clear()
{
	std::scoped_lock lock(m_mtx);
	m_data.clear();
}

#endif // _NETQUEUE_H
