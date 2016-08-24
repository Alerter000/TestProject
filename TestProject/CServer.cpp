#include "CServer.h"

CServer::CServer(const int& port) noexcept : 
	m_port(port), m_serverStarted(false)
{
}

bool CServer::StartServer() noexcept
{
	if (!m_serverStarted)
	{
		m_serverStarted = true;
		try
		{
			CWinSocket::Init();
		}
		catch (const CSocketException& socketException)
		{
			m_serverStarted = false;
		}
		if (m_serverStarted)
		{
			m_serverStarted = m_socketServer.Connect(m_port);
		}

	}
	return m_serverStarted;
}

bool CServer::ConnectServer() noexcept
{
	bool isConnect = m_socketServer.Connect(m_port);
	if (isConnect)
	{
		
	}
	return false;
}

CServer::~CServer() noexcept
{
	m_socketServer.CloseConnection();
}
