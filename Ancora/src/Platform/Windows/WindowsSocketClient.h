#pragma once

#include "Ancora/Network/Socket/SocketClient.h"

#ifndef UNICODE
#define UNICODE 1
#endif

#pragma comment(lib,"Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>

namespace Ancora {

  class WindowsSocketClient : public SocketClient
  {
  public:
    WindowsSocketClient(const SocketClientProps& clientProps);
    virtual ~WindowsSocketClient();

    virtual void Connect(const std::string& address = "127.0.0.1") override;

		virtual std::string Read() override;
		virtual void Send(const std::string& message) override;
  private:
    SocketClientProps m_Props;
		int m_Domain;
		int m_ClientDescriptor;
  };

}
