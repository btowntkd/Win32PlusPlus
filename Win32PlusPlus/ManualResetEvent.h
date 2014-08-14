#pragma once
#include "EventBase.h"

BEGIN_WIN32PP_NAMESPACE

class ManualResetEvent : public EventBase
{
public:
	virtual void Reset()
	{
		::ResetEvent(GetHandle());
	}

	static ManualResetEvent Create()
	{
		HANDLE hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		return ManualResetEvent(hEvent);
	}

protected:
	ManualResetEvent(HANDLE hEvent) :
		EventBase(hEvent)
	{ }
};

END_WIN32PP_NAMESPACE