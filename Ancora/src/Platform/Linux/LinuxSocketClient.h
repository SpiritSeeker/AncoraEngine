#pragma once

#include "Ancora/Network/Socket/SocketClient.h"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

namespace Ancora {

	class LinuxSocketClient : public SocketClient
	{
	public:
		LinuxSocketClient(const SocketClientProps& clientProps);
		virtual ~LinuxSocketClient() = default;

		virtual void Connect(const std::string& address = "127.0.0.1") override;

		virtual std::string Read() override;
		virtual void Send(const std::string& message) override;
	private:
		SocketClientProps m_Props;
		int m_Domain;
		int m_ClientDescriptor;
	};

}
