#ifndef __CSOCKETEXCEPTION_H__
#define __CSOCKETEXCEPTION_H__

#include <exception>
#include <string>

class CSocketException : public std::exception
{

public:
	CSocketException(const std::string& errorMessage) noexcept;
	~CSocketException() noexcept;

public:
	const char* what() const override;

public:
	static const std::string ERROR_SOCKET_INIT;
	static const std::string ERROR_SOCKET_FREE;

private:
	std::string m_messageError;
};

#endif