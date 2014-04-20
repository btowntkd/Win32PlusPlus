#pragma once
#include <string>
#include "LockableBase.h"

BEGIN_WIN32PP_NAMESPACE

class Mutex : public LockableBase
{
public:
	Mutex()
	{
		m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
	};

	Mutex(std::wstring name)
	{
		m_hMutex = ::CreateMutex(NULL, FALSE, name.c_str());
	}

	virtual ~Mutex()
	{
		::CloseHandle(m_hMutex);
	}

	virtual void Lock()
	{
		::WaitForSingleObject(m_hMutex, INFINITE);
	}

	virtual void Unlock()
	{
		::ReleaseMutex(m_hMutex);
	}
private:
	HANDLE m_hMutex;
};

END_WIN32PP_NAMESPACE

