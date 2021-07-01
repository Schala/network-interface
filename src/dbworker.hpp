#ifndef _DBWORKER_H
#define _DBWORKER_H

#include <vector>

#include "tsqueue.hpp"

template <class DB, class Rec> class DBWorker
{
public:
	DBWorker();
	virtual void Close() = 0;
	void Dump(std::vector<Rec> &dest, bool closeDB = true);
	virtual int GetLastResult() = 0;
	virtual std::string_view GetLastError() = 0;
	virtual std::string_view GetLastOp() = 0;
	virtual void Run() = 0;
	void Push(Rec &r);
	DB& GetHandle() const;
protected:
	std::mutex m_mutex;
	DB m_db;
	Rec m_current;
	TSQueue<Rec> m_pending;
};

template <class DB, class Rec>
DBWorker<DB, Rec>::DBWorker()
{
}

template <class DB, class Rec>
void DBWorker<DB, Rec>::Dump(std::vector<Rec> &dest, bool closeDB)
{
	std::scoped_lock lock(m_mutex);

	if (closeDB) Close();
	m_pending.Dump(dest);
}

template <class DB, class Rec>
void DBWorker<DB, Rec>::Push(Rec &r)
{
	std::scoped_lock lock(m_mutex);
	m_pending.PushBack(r);
}

template <class DB, class Rec>
DB& DBWorker<DB, Rec>::GetHandle() const
{
	return m_db;
}

#endif // _DBWORKER_H
