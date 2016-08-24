#include "CWinSocket.h"

WSADATA CWinSocket::m_wsaData;

CWinSocket::CWinSocket() noexcept : m_socket(INVALID_SOCKET)
{
	memset(&m_socketAddress, 0, sizeof(m_socketAddress));
}

CWinSocket::CWinSocket(const CWinSocket& winSocket) noexcept
{
	this->m_socket = winSocket.m_socket;
	this->m_socketAddress.sin_addr = winSocket.m_socketAddress.sin_addr;
	this->m_socketAddress.sin_family = winSocket.m_socketAddress.sin_family;
	this->m_socketAddress.sin_port = winSocket.m_socketAddress.sin_port;
	this->m_isServer = winSocket.m_isServer;
	this->m_isConnect = winSocket.m_isConnect;
}

CWinSocket::~CWinSocket() noexcept
{
	CloseConnection();
}

void CWinSocket::Init() throw(CSocketException) //exception
{
	if (!m_isInitialized)
	{
		m_isInitialized = (WSAStartup(WINSOCKET_VERSION, &m_wsaData) == 0);
		if (!m_isInitialized)
		{
			throw CSocketException(CSocketException::ERROR_SOCKET_INIT);
		}
	}
}

void CWinSocket::Free() throw(CSocketException) //exception
{
	if (m_isInitialized)
	{
		m_isInitialized = (WSACleanup() != 0);
		if (m_isInitialized)
		{
			throw CSocketException(CSocketException::ERROR_SOCKET_FREE);
		}
	}
}

bool CWinSocket::IsConnect() const noexcept
{
	return m_isInitialized && m_isConnect;
}

bool CWinSocket::AcceptClient(ISocket& client) noexcept
{
	bool isAccept = false;
	CWinSocket& winSockClient = dynamic_cast<CWinSocket&>(client);
	if (m_isServer)
	{
		int lenSockAddress = sizeof(winSockClient.m_socketAddress);
		winSockClient.m_socket = accept(winSockClient.m_socket, reinterpret_cast<sockaddr*>(&winSockClient.m_socketAddress), &lenSockAddress);
		isAccept = winSockClient.m_socket != INVALID_SOCKET;
	}
	return isAccept;
}

bool CWinSocket::SendBytes(const ISocket& receiver, const std::vector<unsigned char>& message) noexcept
{
	bool isSend = false;
	const CWinSocket& winSockReceiver = dynamic_cast<const CWinSocket&>(receiver);
	if (receiver.IsConnect())
	{
		isSend = send(winSockReceiver.m_socket, reinterpret_cast<const char*>(message.data()), message.size(), 0) != SOCKET_ERROR;
	}
	return isSend;
}

bool CWinSocket::ReceiveBytes(const ISocket& sender, std::vector<unsigned char>& message) noexcept
{
	bool isReceive = false;
	if (sender.IsConnect())
	{
		const CWinSocket& winSockSender = dynamic_cast<const CWinSocket&>(sender);
		char recievedMessage[MAX_LEN_MESSAGE];
		int lenMessage = recv(winSockSender.m_socket, recievedMessage, MAX_LEN_MESSAGE, 0);
		isReceive = lenMessage != SOCKET_ERROR;
		if (isReceive)
		{
			message.clear();
			std::copy(recievedMessage, recievedMessage + lenMessage, message.begin());
		}
	}
	return isReceive;
}

bool CWinSocket::Connect(const int& port, const std::string& ipAddress)
{
	if (!m_isConnect)
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		bool socketIsInit = m_socket != INVALID_SOCKET;
		bool socketAddressIsInit = InitSockAddress(ipAddress, port);
		if (socketIsInit && socketAddressIsInit)
		{
			m_isConnect = BindSocketAndAddress();
		}
	}
	return m_isConnect;
}

bool CWinSocket::CloseConnection()
{
	if (m_isConnect && m_socket != INVALID_SOCKET)
	{
		m_isServer = false;
		m_isConnect = closesocket(m_socket) != 0;
	}
	return !m_isConnect;
}

CWinSocket& CWinSocket::operator=(const CWinSocket& winSocket) noexcept
{
	this->m_socket = winSocket.m_socket;
	this->m_socketAddress.sin_addr = winSocket.m_socketAddress.sin_addr;
	this->m_socketAddress.sin_family = winSocket.m_socketAddress.sin_family;
	this->m_socketAddress.sin_port = winSocket.m_socketAddress.sin_port;
	this->m_isServer = winSocket.m_isServer;
	this->m_isConnect = winSocket.m_isConnect;
	return *this;
}

bool CWinSocket::InitSockAddress(const std::string& ipAddress, const int& port)
{
	m_socketAddress.sin_family = AF_INET;
	m_socketAddress.sin_port = htons(port);
	m_socketAddress.sin_addr.S_un.S_addr = (ipAddress.empty() ? 0 : inet_addr(ipAddress.data()));
	return (m_socketAddress.sin_addr.S_un.S_addr != INADDR_NONE);
}

bool CWinSocket::BindSocketAndAddress()
{
	bool isBind = false;
	if (m_socketAddress.sin_addr.S_un.S_addr == 0)
	{
		m_isServer = true;
		isBind = bind(m_socket, reinterpret_cast<sockaddr*>(&m_socketAddress), sizeof(m_socketAddress)) == 0;
		bool isListen = Listen();
		isBind = isBind && isListen;
	}
	else
	{
		isBind = connect(m_socket, reinterpret_cast<sockaddr*>(&m_socketAddress), sizeof(m_socketAddress)) == 0;
		m_isServer = false;
	}
	return isBind;
}

bool CWinSocket::Listen()
{
	bool isListen = false;
	if (m_isServer)
	{
		isListen = listen(m_socket, MAX_CONNECTION) != SOCKET_ERROR;
	}
	return isListen;
}
