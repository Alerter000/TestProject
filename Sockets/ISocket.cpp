#include "ISocket.h"

std::atomic<bool> ISocket::m_isInitialized = false;

ISocket::ISocket() noexcept : m_isConnect(false), m_isServer(false)
{
}

ISocket::~ISocket() noexcept
{
}