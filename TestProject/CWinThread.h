#ifndef __CWINTHREAD_H__
#define __CWINTHREAD_H__

#include <Windows.h>

class CWinThread
{
public:
	CWinThread() noexcept;
	~CWinThread() noexcept;

public:
	bool StartThread(HANDLE handleThread) noexcept;
	void StopThread() noexcept;

private:
	HANDLE m_threadHandle;

};

#endif // !__CWINTHREAD_H__
