#ifndef __CWINSOCKET_H__
#define __CWINSOCKET_H__

#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501
#define _WIN32_IE 0x0600
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#include "ISocket.h"
#include "CSocketException.h"

class CWinSocket : public ISocket
{
public:
	CWinSocket() noexcept;
	explicit CWinSocket(const CWinSocket& winSocket) noexcept;
	~CWinSocket() noexcept;

public:
	static void Init() throw(CSocketException); //exception
	static void Free() throw(CSocketException); //exception
	
	bool Connect(const int& port, const std::string& ipAddress = "") override;
	bool CloseConnection() override;

	bool IsConnect() const noexcept override;
	bool AcceptClient(ISocket& client) noexcept override;
	bool SendBytes(const ISocket& receiver, const std::vector<unsigned char>& message) noexcept override;
	bool ReceiveBytes(const ISocket& sender, std::vector<unsigned char>& message) noexcept override;

	CWinSocket& operator=(const CWinSocket& winSocket) noexcept;

private:
	bool InitSockAddress(const std::string& ipAddress, const int& port);
	bool BindSocketAndAddress();
	bool Listen();

private:
	static constexpr const int WINSOCKET_VERSION = MAKEWORD(2, 2);

private:
	SOCKET m_socket;
	sockaddr_in m_socketAddress;
	static WSADATA m_wsaData;
};

#endif // !__CWINSOCKET_H__

