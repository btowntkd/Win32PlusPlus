#pragma once

BEGIN_WIN32PP_NAMESPACE


class Thread
{
public:
	Thread(HANDLE hThread) :
		m_hThread(hThread)
	{ }
	virtual ~Thread(void) { }

	bool IsAlive() 
	{
		return ::WaitForSingleObject(m_hThread, 0) == WAIT_TIMEOUT;
	}

	void Join() 
	{
		::WaitForSingleObject(m_hThread, INFINITE);
	}
	void Join(DWORD timeoutMilliseconds)
	{
		::WaitForSingleObject(m_hThread, timeoutMilliseconds);
	}

	static Thread Create(LPTHREAD_START_ROUTINE fpStartRoutine, LPVOID pParam)
	{
		HANDLE hThread = ::CreateThread(NULL, NULL, fpStartRoutine, pParam, NULL, NULL);
		return Thread(hThread);
	}

private:
	HANDLE m_hThread;
};

END_WIN32PP_NAMESPACE

