#include "fipch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Flick {

	std::shared_ptr<spdlog::logger> Log::m_Corelogger;
	std::shared_ptr<spdlog::logger> Log::m_Clientlogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_Corelogger = spdlog::stdout_color_mt("FLICK");
		m_Corelogger->set_level(spdlog::level::trace);

		m_Clientlogger = spdlog::stdout_color_mt("APP");
		m_Clientlogger->set_level(spdlog::level::trace);
	}

}