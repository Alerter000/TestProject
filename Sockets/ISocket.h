#ifndef __ISOCKET_H__
#define __ISOCKET_H__

#include <atomic>
#include <string>
#include <vector>

class ISocket
{
public:
	ISocket() noexcept;
	virtual ~ISocket() noexcept;

public:
	virtual bool Connect(const int& port, const std::string& ipAddress = "") = 0;
	virtual bool CloseConnection() = 0;
	virtual bool IsConnect() const noexcept = 0;
	virtual bool AcceptClient(ISocket& client) noexcept = 0;
	virtual bool SendBytes(const ISocket& receiver, const std::vector<unsigned char>& message) noexcept = 0;
	virtual bool ReceiveBytes(const ISocket& sender, std::vector<unsigned char>& message) noexcept = 0;

public:
	static const int MAX_LEN_MESSAGE = 4096;
	static const int MAX_CONNECTION = 10;

protected:
	static std::atomic<bool> m_isInitialized;
	bool m_isConnect;
	bool m_isServer;
};

#endif // !__ISOCKET_H__

