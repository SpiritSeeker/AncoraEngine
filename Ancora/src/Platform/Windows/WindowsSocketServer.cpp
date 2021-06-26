#include "aepch.h"
#include "WindowsSocketServer.h"

namespace Ancora {

  WindowsSocketServer::WindowsSocketServer(const SocketServerProps& serverProps)
		: m_Props(serverProps)
	{
		m_Domain = m_Props.UseIPv6 ? AF_INET6 : AF_INET;
		int connectionType = m_Props.UseTCP ? SOCK_STREAM : SOCK_DGRAM;
    int connectionProtocol = m_Props.UseTCP ? IPPROTO_TCP : IPPROTO_UDP;
    m_Address.sin_family = m_Domain;
		m_Address.sin_addr.s_addr = INADDR_ANY;
		m_Address.sin_port = htons(m_Props.Port);
    WSADATA wsaData = { 0 };

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
      AE_CORE_ERROR("SERVER ERROR: WSA startup failed!");
      return;
    }

	m_ServerDescriptor = socket(m_Domain, connectionType, connectionProtocol);
    if (m_ServerDescriptor == INVALID_SOCKET)
    {
      AE_CORE_ERROR("SERVER ERROR: Socket creation failed!");
      return;
    }
	}

  WindowsSocketServer::~WindowsSocketServer()
  {
    closesocket(m_ServerDescriptor);
    WSACleanup();
  }

	void WindowsSocketServer::Bind(int queueLength)
	{
		int addressLength = sizeof(m_Address);

		if (bind(m_ServerDescriptor, (struct sockaddr*)&m_Address, addressLength) < 0)
		{
			AE_CORE_ERROR("SERVER ERROR: Failed to bind!");
			return;
		}

		if (listen(m_ServerDescriptor, queueLength) < 0)
		{
			AE_CORE_ERROR("SERVER ERROR: Failed to start listening for connections!");
			return;
		}

		AE_CORE_INFO("SERVER INFO: Listening for connections!");
	}

	int WindowsSocketServer::Accept()
	{
		int addressLength = sizeof(m_Address);
		int newSocket;

		if ((newSocket = accept(m_ServerDescriptor, (struct sockaddr*)&m_Address, (socklen_t*)&addressLength)) < 0)
		{
			AE_CORE_ERROR("SERVER ERROR: Failed to accept new connection!");
			return -1;
		}

		m_ActiveConnection = newSocket;
		return newSocket;
	}

	std::string WindowsSocketServer::Read(int socket)
	{
		if (socket == -1) socket = m_ActiveConnection;
		if (socket == -1)
		{
			AE_CORE_ERROR("SERVER ERROR: No active connection to read!");
			std::string blankString("");
			return blankString;
		}

		char *buffer = new char[m_Props.BufferSize];
		uint32_t readSize = recv(socket, buffer, m_Props.BufferSize, 0);

		std::string data(buffer, readSize);
		delete[] buffer;

		return data;
	}

	void WindowsSocketServer::Send(const std::string& message, int socket)
	{
		if (socket == -1) socket = m_ActiveConnection;
		if (socket == -1)
		{
			AE_CORE_ERROR("SERVER ERROR: No active connection to send to!");
			return;
		}

		send(socket, message.c_str(), message.size(), 0);
	}

	Ref<SocketServer> SocketServer::Create(const SocketServerProps& serverProps)
	{
		return CreateRef<WindowsSocketServer>(serverProps);
	}

}
