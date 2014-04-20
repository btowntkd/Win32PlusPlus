#pragma once

BEGIN_WIN32PP_NAMESPACE

class LockableBase
{
public:

	LockableBase(void);
	virtual ~LockableBase(void);

	virtual void Lock() = 0;
	virtual void Unlock() = 0;
};

END_WIN32PP_NAMESPACE

