#pragma once

#ifdef FI_PLATFORM_WINDOWS

extern Flick::Application* Flick::CreateApplication();

int main(int argc, char** argv)
{
	Flick::Log::Init();
	FI_CORE_WARN("initialized log!");
	int a = 5;
	FI_INFO("This is flick! Var={}", a);

	auto app = Flick::CreateApplication();
	app->Run();
	delete app;
}

#endif // it is an entry point which is called by the application
