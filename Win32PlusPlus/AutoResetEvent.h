#pragma once
#include "EventBase.h"

BEGIN_WIN32PP_NAMESPACE

class AutoResetEvent : EventBase
{
public:

	static AutoResetEvent Create()
	{
		HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		return AutoResetEvent(hEvent);
	}

protected:
	AutoResetEvent(HANDLE hEvent) :
		EventBase(hEvent)
	{ }
};

END_WIN32PP_NAMESPACE