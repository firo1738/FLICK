#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Flick {
	class FLICK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_Corelogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_Clientlogger; }
	private:
		static std::shared_ptr<spdlog::logger> m_Corelogger;
		static std::shared_ptr<spdlog::logger> m_Clientlogger;
	};
}

//core log macros
#define FI_CORE_TRACE(...) ::Flick::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FI_CORE_INFO(...)  ::Flick::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FI_CORE_WARN(...)  ::Flick::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FI_CORE_ERROR(...) ::Flick::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FI_CORE_CRITICAL(...) ::Flick::Log::GetCoreLogger()->critical(__VA_ARGS__)

//client log macros
#define FI_TRACE(...) ::Flick::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FI_INFO(...)  ::Flick::Log::GetClientLogger()->info(__VA_ARGS__)
#define FI_WARN(...)  ::Flick::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FI_ERROR(...) ::Flick::Log::GetClientLogger()->error(__VA_ARGS__)
#define FI_CRITICAL(...) ::Flick::Log::GetClientLogger()->critical(__VA_ARGS__)