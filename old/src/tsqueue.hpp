#ifndef _TSQUEUE_H
#define _TSQUEUE_H

#include <condition_variable>
#include <cstdint>
#include <deque>
#include <mutex>
#include <utility>
#include <vector>

/// Thread-safe queue
template <class T> class TSQueue
{
public:
	/// Constructs a new, empty queue
	TSQueue() = default;

	/// Queue cannot be copy-constructed
	TSQueue(const TSQueue<T>&) = delete;

	/// Clears the queue before deallocation
	virtual ~TSQueue();

	/// Reference to the front element of the queue
	const T& Front() const;

	/// Reference to the last element of the queue
	const T& Back() const;

	/**
	 * Appends an element to the end of the queue
	 * @param item Item to append
	 */
	void PushBack(const T &item);

	/**
	 * Appends an element to the front of the queue
	 * @param item Item to append
	 */
	void PushFront(const T &item);

	/// Is the queue empty?
	bool IsEmpty() const;

	/// Number of elements in the queue
	size_t Size() const;

	/// Clears the queue of all elements
	void Clear();

	/// Removes and returns the frontmost element
	T PopFront();

	/// Removes and returns the last element
	T PopBack();

	/// Retains the queue until more work arrives
	void Wait();

	/// Dumps all elements of the queue into a vector
	void Dump(std::vector<T> &dest);

private:
	std::mutex m_mutex;
	std::deque<T> m_queue;
	std::condition_variable m_blocking;
};

template <class T>
TSQueue<T>::~TSQueue()
{
	Clear();
}

template <class T>
const T& TSQueue<T>::Front() const
{
	return m_queue.front();
}

template <class T>
const T& TSQueue<T>::Back() const
{
	return m_queue.back();
}

template <class T>
void TSQueue<T>::PushBack(const T &item)
{
	std::scoped_lock lock(m_mutex);
	m_queue.emplace_back(std::move(item));
}

template <class T>
void TSQueue<T>::PushFront(const T &item)
{
	std::scoped_lock lock(m_mutex);
	m_queue.emplace_front(std::move(item));
}

template <class T>
bool TSQueue<T>::IsEmpty() const
{
	return m_queue.empty();
}

template <class T>
size_t TSQueue<T>::Size() const
{
	return m_queue.size();
}

template <class T>
void TSQueue<T>::Clear()
{
	std::scoped_lock lock(m_mutex);
	m_queue.clear();
}

template <class T>
T TSQueue<T>::PopFront()
{
	std::scoped_lock lock(m_mutex);
	auto item = std::move(m_queue.front());
	m_queue.pop_front();
	return item;
}

template <class T>
T TSQueue<T>::PopBack()
{
	std::scoped_lock lock(m_mutex);
	auto item = std::move(m_queue.back());
	m_queue.pop_back();
	return item;
}

template <class T>
void TSQueue<T>::Wait()
{
	while (IsEmpty())
	{
		std::unique_lock lock(m_mutex);
		m_blocking.wait(lock);
	}
}

template <class T>
void TSQueue<T>::Dump(std::vector<T> &dest)
{
	std::scoped_lock lock(m_mutex);

	for (auto &e : m_queue)
		dest.push_back(e);
}

#endif // _TSQUEUE_H
