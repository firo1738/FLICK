#pragma once

#include "Flick/Core/Core.h"

#ifdef FI_PLATFORM_WINDOWS

extern Flick::Application* Flick::CreateApplication();

int main(int argc, char** argv)
{
	Flick::Log::Init();

	FI_PROFILE_BEGIN_SESSION("Startup", "FlickProfile-Startup.json");
	auto app = Flick::CreateApplication();
	FI_PROFILE_END_SESSION();

	FI_PROFILE_BEGIN_SESSION("Runtime", "FlickProfile-Runtime.json");
	app->Run();
	FI_PROFILE_END_SESSION();

	FI_PROFILE_BEGIN_SESSION("Shutdown", "FlickProfile-Shutdown.json");
	delete app;
	FI_PROFILE_END_SESSION();
}

#endif // it is an entry point which is called by the application
