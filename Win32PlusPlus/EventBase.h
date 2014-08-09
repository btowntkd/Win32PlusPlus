#pragma once

BEGIN_WIN32PP_NAMESPACE

class EventBase
{
public:
	virtual ~EventBase(void) { }

	virtual bool IsSignaled()
	{
		return ::WaitForSingleObject(m_hEvent, 0) == WAIT_TIMEOUT;
	}

	virtual void Wait()
	{
		::WaitForSingleObject(m_hEvent, INFINITE);
	}

	virtual bool Wait(DWORD timeoutMilliseconds)
	{
		return ::WaitForSingleObject(m_hEvent, timeoutMilliseconds) == WAIT_OBJECT_0;
	}

	virtual void Signal()
	{
		::SetEvent(m_hEvent);
	}

	HANDLE GetHandle()
	{
		return m_hEvent;
	}

protected:
	EventBase(HANDLE hEvent) :
		m_hEvent(hEvent)
	{ }

private:
	HANDLE m_hEvent;
};

END_WIN32PP_NAMESPACE