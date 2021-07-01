#include "dbworker.hpp"

PalaceDBWorker::PalaceDBWorker(const std::filesystem::path &dbPath):
	SQLiteWorker(dbPath)
{
}

void PalaceDBWorker::Run()
{
	if (!m_db) return;

	if (!m_pending.IsEmpty())
	{
		std::scoped_lock lock(m_mutex);
		SQLiteRec rec = m_pending.PopFront();
		char *err = nullptr;

		switch (rec.kind)
		{
			case SQLiteOpType::Read:
				break;
			case SQLiteOpType::Write:
				rec.result = sqlite3_exec(m_db, rec.op.data(), nullptr, nullptr, &err);
		}

		if (err)
		{
			rec.error = err;
			sqlite3_free(err);
		}
	}

	Run();
}
