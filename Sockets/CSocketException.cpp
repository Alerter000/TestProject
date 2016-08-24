#include "CSocketException.h"

const std::string CSocketException::ERROR_SOCKET_INIT = "Winsock not be initialized!";
const std::string CSocketException::ERROR_SOCKET_FREE = "Winsock not be closed!";

CSocketException::CSocketException(const std::string& errorMessage) noexcept : m_messageError(errorMessage)
{

}

CSocketException::~CSocketException() noexcept
{
}

const char* CSocketException::what() const
{
	return m_messageError.data();
}
