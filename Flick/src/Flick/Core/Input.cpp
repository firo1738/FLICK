#include "fipch.h"
#include "Flick/Core/Input.h"

#ifdef FI_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif // FI_PLATFORM_WINDOWS

namespace Flick
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef FI_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
	#else 
		FI_CORE_ASSERT(false, "Unknown Platform!");
		return nullptr;
	#endif
	}
}