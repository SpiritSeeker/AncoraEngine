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
		SocketClient(const SocketClientProps& clientProps);
		~SocketClient() = default;

		void Connect(const std::string& address = "127.0.0.1");

		std::string Read();
		void Send(const std::string& message);

		static Ref<SocketClient> Create(const SocketClientProps& clientProps = SocketClientProps());
	private:
		SocketClientProps m_Props;
		int m_Domain;
		int m_ClientDescriptor;
	};

}
