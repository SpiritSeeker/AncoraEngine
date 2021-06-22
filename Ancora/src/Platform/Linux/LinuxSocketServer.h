#pragma once

#include "Ancora/Network/Socket/SocketServer.h"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

namespace Ancora {

  class LinuxSocketServer : public SocketServer
  {
  public:
    LinuxSocketServer(const SocketServerProps& serverProps);
    virtual ~LinuxSocketServer() = default;

		virtual void Bind(int queueLength = 3) override;
		virtual int Accept() override;

		virtual std::string Read(int socket = -1) override;
		virtual void Send(const std::string& message, int socket = -1) override;
	private:
		SocketServerProps m_Props;
		int m_Domain;
		int m_ServerDescriptor;
		struct sockaddr_in m_Address;
		int activeConnection = -1;
	};

}
