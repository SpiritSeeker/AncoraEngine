#include "aepch.h"
#include "LinuxSocketServer.h"

namespace Ancora {

  LinuxSocketServer::LinuxSocketServer(const SocketServerProps& serverProps)
		: m_Props(serverProps)
	{
		m_Domain = m_Props.UseIPv6 ? AF_INET6 : AF_INET;
		int connectionType = m_Props.UseTCP ? SOCK_STREAM : SOCK_DGRAM;

		if ((m_ServerDescriptor = socket(m_Domain, connectionType, 0)) == 0)
		{
			AE_CORE_ERROR("SERVER ERROR: Socket creation failed!");
			return;
		}

		int opt = 1;
		if (setsockopt(m_ServerDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		{
			AE_CORE_ERROR("SERVER ERROR: Failed to add options to socket!");
			return;
		}
	}

	void LinuxSocketServer::Bind(int queueLength)
	{
		int addressLength = sizeof(m_Address);

		m_Address.sin_family = m_Domain;
		m_Address.sin_addr.s_addr = INADDR_ANY;
		m_Address.sin_port = htons(m_Props.Port);

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

	int LinuxSocketServer::Accept()
	{
		int addressLength = sizeof(m_Address);
		int newSocket;

		if ((newSocket = accept(m_ServerDescriptor, (struct sockaddr*)&m_Address, (socklen_t*)&addressLength)) < 0)
		{
			AE_CORE_ERROR("SERVER ERROR: Failed to accept new connection!");
			return -1;
		}

		activeConnection = newSocket;
		return newSocket;
	}

	std::string LinuxSocketServer::Read(int socket)
	{
		if (socket == -1) socket = activeConnection;
		if (socket == -1)
		{
			AE_CORE_ERROR("SERVER ERROR: No active connection to read!");
			std::string blankString("");
			return blankString;
		}

		char *buffer = new char[m_Props.BufferSize];
		uint32_t readSize = read(socket, buffer, m_Props.BufferSize);

		std::string data(buffer, readSize);
		delete[] buffer;

		return data;
	}

	void LinuxSocketServer::Send(const std::string& message, int socket)
	{
		if (socket == -1) socket = activeConnection;
		if (socket == -1)
		{
			AE_CORE_ERROR("SERVER ERROR: No active connection to send to!");
			return;
		}

		send(socket, message.c_str(), message.size(), 0);
	}

	Ref<SocketServer> SocketServer::Create(const SocketServerProps& serverProps)
	{
		return CreateRef<LinuxSocketServer>(serverProps);
	}

}
