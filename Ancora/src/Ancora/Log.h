#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Ancora {

	class ANCORA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define AE_CORE_TRACE(...)   ::Ancora::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AE_CORE_INFO(...)    ::Ancora::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AE_CORE_WARN(...)    ::Ancora::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AE_CORE_ERROR(...)   ::Ancora::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AE_CORE_FATAL(...)   ::Ancora::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define AE_TRACE(...)   ::Ancora::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AE_INFO(...)    ::Ancora::Log::GetClientLogger()->info(__VA_ARGS__)
#define AE_WARN(...)    ::Ancora::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AE_ERROR(...)   ::Ancora::Log::GetClientLogger()->error(__VA_ARGS__)
#define AE_FATAL(...)   ::Ancora::Log::GetClientLogger()->fatal(__VA_ARGS__)