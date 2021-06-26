#include "aepch.h"
#include "WindowsSocketClient.h"

namespace Ancora {

  WindowsSocketClient::WindowsSocketClient(const SocketClientProps& clientProps)
    : m_Props(clientProps)
  {
    m_Domain = m_Props.UseIPv6 ? AF_INET6 : AF_INET;
    int connectionType = m_Props.UseTCP ? SOCK_STREAM : SOCK_DGRAM;
    int connectionProtocol = m_Props.UseTCP ? IPPROTO_TCP : IPPROTO_UDP;
    WSADATA wsaData = { 0 };

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
      AE_CORE_ERROR("CLIENT ERROR: WSA startup failed!");
      return;
    }

    if ((m_ClientDescriptor = socket(m_Domain, connectionType, connectionProtocol)) == INVALID_SOCKET)
    {
      AE_CORE_ERROR("CLIENT ERROR: Socket creation failed!");
      return;
    }
  }

  WindowsSocketClient::~WindowsSocketClient()
  {
    closesocket(m_ClientDescriptor);
    WSACleanup();
  }

  void WindowsSocketClient::Connect(const std::string& address)
  {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = m_Domain;
    serverAddress.sin_port = htons(m_Props.Port);

    if (inet_pton(m_Domain, address.c_str(), &serverAddress.sin_addr) <= 0)
    {
      AE_CORE_ERROR("CLIENT ERROR: Invalid server address!");
      return;
    }

    if (connect(m_ClientDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
      AE_CORE_ERROR("CLIENT ERROR: Failed to connect to server!");
      return;
    }

    AE_CORE_INFO("CLIENT INFO: Connected to {0}", address);
  }

  std::string WindowsSocketClient::Read()
  {
    char *buffer = new char[m_Props.BufferSize];
    uint32_t readSize = recv(m_ClientDescriptor, buffer, m_Props.BufferSize, 0);

    std::string data(buffer, readSize);
    delete[] buffer;

    return data;
  }

  void WindowsSocketClient::Send(const std::string& message)
  {
    send(m_ClientDescriptor, message.c_str(), message.size(), 0);
  }

  Ref<SocketClient> SocketClient::Create(const SocketClientProps& clientProps)
  {
    return CreateRef<WindowsSocketClient>(clientProps);
  }

}
