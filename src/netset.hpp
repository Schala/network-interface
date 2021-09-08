#ifndef _NETSET_H
#define _NETSET_H

#include <mutex>
#include <optional>
#include <set>
#include <utility>

// Thread-safe set using a lockable mutex
template <class T> class NetSet
{
public:
	typedef std::set<T>::const_iterator ConstIteratorType;
	typedef std::set<T>::iterator IteratorType;
	typedef std::pair<IteratorType, bool> IterBoolPairType;
	typedef std::set<T>::size_type SizeType;

	NetSet() = default;

	// If T has a custom null constant
	NetSet(const T& nullValue);

	// Sets cannot be copied
	NetSet(const NetSet<T>&) = delete;

	// Returns either a valid element or a null element
	T& Find(const T &key);

	// Inserts an element into the set
	IterBoolPairType Insert(const T &value);

	// Clears all data
	void Clear();

	// Erases an element from the set
	SizeType Erase(const T &key);

	// Is the set empty?
	bool IsEmpty();

	// Returns a constant iterator to the beginning of the set
	ConstIteratorType cbegin();

	// Returns a constant iterator to the beginning of the set
	ConstIteratorType cend();
private:
	std::mutex m_mtx;
	std::optional<T> m_null;
	std::set<T> m_data;
};

template <class T>
NetSet<T>::NetSet(const T& nullValue):
	m_null(nullValue)
{
}

template <class T>
T& NetSet<T>::Find(const T &key)
{
	std::scoped_lock lock(m_mtx);

	ConstIteratorType result = m_data.find(key);

	if (result == m_data.end() && m_null)
		return m_null;
	else
		return T();
	
	return *result;
}

template <class T>
NetSet<T>::IterBoolPairType NetSet<T>::Insert(const T &value)
{
	std::scoped_lock lock(m_mtx);
	return m_data.insert(value);
}

template <class T>
void NetSet<T>::Clear()
{
	std::scoped_lock lock(m_mtx);
	m_data.clear();
}

template <class T>
NetSet<T>::SizeType NetSet<T>::Erase(const T &key)
{
	std::scoped_lock lock(m_mtx);
	return m_data.erase(key);
}

template <class T>
bool NetSet<T>::IsEmpty()
{
	std::scoped_lock lock(m_mtx);
	return m_data.empty();
}

template <class T>
NetSet<T>::ConstIteratorType NetSet<T>::cbegin()
{
	std::scoped_lock lock(m_mtx);
	return m_data.cbegin();
}

template <class T>
NetSet<T>::ConstIteratorType NetSet<T>::cend()
{
	std::scoped_lock lock(m_mtx);
	return m_data.cend();
}

#endif // _NETSET_H
