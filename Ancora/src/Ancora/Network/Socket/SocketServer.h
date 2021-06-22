#pragma once

namespace Ancora {

  struct SocketServerProps
  {
    bool UseTCP = true;
    bool UseIPv6 = false;
    uint32_t Port = 8080;
    uint32_t BufferSize = 1024;
  };

  class SocketServer
  {
  public:
    virtual ~SocketServer() {}

    virtual void Bind(int queueLength) = 0;
    virtual int Accept() = 0;

    virtual std::string Read(int socket) = 0;
    virtual void Send(const std::string& message, int socket) = 0;

    static Ref<SocketServer> Create(const SocketServerProps& serverProps = SocketServerProps());
  };

}
