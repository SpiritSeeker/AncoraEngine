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
    SocketServer(const SocketServerProps& serverProps);
    ~SocketServer() = default;

		void Bind(int queueLength = 3);
		int Accept();

		std::string Read(int socket = -1);
		void Send(const std::string& message, int socket = -1);

		static Ref<SocketServer> Create(const SocketServerProps& serverProps = SocketServerProps());
	private:
		SocketServerProps m_Props;
		int m_Domain;
		int m_ServerDescriptor;
		struct sockaddr_in m_Address;
		int activeConnection = -1;
	};

}
