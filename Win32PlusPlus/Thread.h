#pragma once

BEGIN_WIN32PP_NAMESPACE

enum ThreadJoinResult
{
	TimedOut,
	Complete
};

class Thread
{
public:
	Thread(HANDLE hThread) :
		m_hThread(hThread)
	{ }
	virtual ~Thread(void) { }

	bool IsAlive() { return (Join(0) == ThreadJoinResult::TimedOut); }

	ThreadJoinResult Join() { return Join(INFINITE); }
	ThreadJoinResult Join(DWORD timeoutMilliseconds)
	{
		DWORD waitResult = ::WaitForSingleObject(m_hThread, timeoutMilliseconds);
		if(waitResult == WAIT_TIMEOUT) return ThreadJoinResult::TimedOut;
		else if(waitResult == WAIT_OBJECT_0) return ThreadJoinResult::Complete;
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

