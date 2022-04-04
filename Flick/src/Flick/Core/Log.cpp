#include "fipch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Flick {

	Ref<spdlog::logger> Log::s_Corelogger;
	Ref<spdlog::logger> Log::s_Clientlogger;

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(CreateRef<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("Flick.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_Corelogger = CreateRef<spdlog::logger>("Flick", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_Corelogger);
		s_Corelogger->set_level(spdlog::level::trace);

		s_Clientlogger = CreateRef<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_Clientlogger);
		s_Clientlogger->set_level(spdlog::level::trace);
		s_Clientlogger->flush_on(spdlog::level::trace);
	}

}