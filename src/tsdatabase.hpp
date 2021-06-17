#ifndef _TSDATABASE_H
#define _TSDATABASE_H

#include <vector>

#include "tsqueue.hpp"

template <class DB, class Rec> class TSDatabase
{
public:
	virtual void Close() = 0;
	void Dump(std::vector<Rec> &dest, bool closeDB = true);
	virtual int GetLastResult() const = 0;
	virtual std::string_view& GetLastError() const = 0;
	virtual std::string_view& GetLastOp() const = 0;
	virtual void Run() = 0;
	void Push(Rec &r);
	DB& GetHandle() const;
protected:
	std::mutex m_mutex;
	DB m_db;
private:
	TSQueue<Rec> m_pending;
	Rec m_current;
};

template <class DB, class Rec>
void TSDatabase<DB, Rec>::Dump(std::vector<Rec> &dest, bool closeDB)
{
	std::scoped_lock lock(m_mutex);

	if (closeDB) Close();
	m_pending.Dump(dest);
}

template <class DB, class Rec>
void TSDatabase<DB, Rec>::Push(Rec &r)
{
	std::scoped_lock lock(m_mutex);
	m_pending.PushBack(r);
}

template <class DB, class Rec>
DB& TSDatabase<DB, Rec>::GetHandle() const
{
	return m_db;
}

#endif // _TSDATABASE_H
