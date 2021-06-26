#pragma once

#include "Ancora/Network/Socket/SocketServer.h"

#ifndef UNICODE
#define UNICODE 1
#endif

#pragma comment(lib,"Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

namespace Ancora {

  class WindowsSocketServer : public SocketServer
  {
  public:
    WindowsSocketServer(const SocketServerProps& serverProps);
    virtual ~WindowsSocketServer();

		virtual void Bind(int queueLength = 3) override;
		virtual int Accept() override;

		virtual std::string Read(int socket = -1) override;
		virtual void Send(const std::string& message, int socket = -1) override;
	private:
		SocketServerProps m_Props;
		int m_Domain;
		int m_ServerDescriptor;
		struct sockaddr_in m_Address;
		int m_ActiveConnection = -1;
	};

}
