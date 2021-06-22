#pragma once

namespace Ancora {

  struct SocketClientProps
	{
		bool UseTCP = true;
		bool UseIPv6 = false;
		uint32_t Port = 8080;
		uint32_t BufferSize = 1024;
	};

  class SocketClient
  {
  public:
    virtual ~SocketClient() {}

    virtual void Connect(const std::string& address) = 0;

    virtual std::string Read() = 0;
    virtual void Send(const std::string& message) = 0;

    static Ref<SocketClient> Create(const SocketClientProps& clientProps = SocketClientProps());
  };

}
