#pragma once
#include "LockableBase.h"

BEGIN_WIN32PP_NAMESPACE

class CriticalSection : public LockableBase
{
public:
	CriticalSection()
	{
		::InitializeCriticalSection(&m_criticalSection);
	};

	CriticalSection(DWORD spinCount)
	{
		::InitializeCriticalSectionAndSpinCount(&m_criticalSection, spinCount);
	}

	virtual ~CriticalSection()
	{
		::DeleteCriticalSection(&m_criticalSection);
	}

	virtual void Lock()
	{
		::EnterCriticalSection(&m_criticalSection);
	}

	virtual void Unlock()
	{
		::LeaveCriticalSection(&m_criticalSection);
	}
private:
	CRITICAL_SECTION m_criticalSection;
};

END_WIN32PP_NAMESPACE