#include "CWinThread.h"

CWinThread::CWinThread() : m_threadHandle(NULL)
{
}

CWinThread::~CWinThread()
{
	if (m_threadHandle)
		CloseHandle(m_threadHandle);
}

bool CWinThread::StartThread(HANDLE handleThread) noexcept
{

	return false;
}
