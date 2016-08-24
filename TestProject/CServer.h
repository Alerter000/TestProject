#ifndef __CSERVER_H__
#define __CSERVER_H__

#include <Windows.h>

#include <atomic>
#include <vector>

#include "CWinSocket.h"

class CServer
{
public:
	explicit CServer(const int& port) noexcept;
	~CServer() = default;

public:
	bool StartServer() noexcept;
	void StopServer() noexcept;

private:
	bool ConnectServer() noexcept;

private:
	CWinSocket m_socketServer;
	int m_port;
	std::atomic<bool> m_serverStarted;
	std::vector<HANDLE> m_threadPool;
};
	

#endif // !__CSERVER_H__
