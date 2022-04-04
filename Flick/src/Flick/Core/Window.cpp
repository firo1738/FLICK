#include "fipch.h"
#include "Flick/Core/Window.h"

#ifdef FI_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Flick
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef FI_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		FI_CORE_ASSERT(false, "Unknown Platform!");
		return nullptr;
	#endif
	}
}