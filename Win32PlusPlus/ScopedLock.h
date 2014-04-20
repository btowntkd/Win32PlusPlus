#pragma once
#include "LockableBase.h"

BEGIN_WIN32PP_NAMESPACE

class ScopedLock
{
public:
	ScopedLock(LockableBase& lockable) :
		m_lockable(lockable)
	{
		m_lockable.Lock();
	};

	virtual ~ScopedLock()
	{
		m_lockable.Unlock();
	}
private:
	LockableBase& m_lockable;
};

END_WIN32PP_NAMESPACE

