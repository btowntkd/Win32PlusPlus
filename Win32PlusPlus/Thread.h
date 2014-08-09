#pragma once

BEGIN_WIN32PP_NAMESPACE

class Thread
{
public:
	virtual ~Thread(void) { }

	virtual bool IsAlive()
	{
		return ::WaitForSingleObject(m_hThread, 0) == WAIT_TIMEOUT;
	}

	virtual void Join()
	{
		::WaitForSingleObject(m_hThread, INFINITE);
	}

	virtual bool Join(DWORD timeoutMilliseconds)
	{
		return ::WaitForSingleObject(m_hThread, timeoutMilliseconds) == WAIT_OBJECT_0;
	}

	HANDLE GetHandle()
	{
		return m_hThread;
	}

	static Thread Create(LPTHREAD_START_ROUTINE fpStartRoutine, LPVOID pParam)
	{
		HANDLE hThread = ::CreateThread(NULL, NULL, fpStartRoutine, pParam, NULL, NULL);
		return Thread(hThread);
	}

	static Thread FromHandle(HANDLE hThread)
	{
		return Thread(hThread);
	}

protected:
	Thread(HANDLE hThread) :
		m_hThread(hThread)
	{ }

private:
	HANDLE m_hThread;
};

END_WIN32PP_NAMESPACE

