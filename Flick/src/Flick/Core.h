#pragma once

#ifdef FI_PLATFORM_WINDOWS
#if FI_DYNAMIC_LINK
	#ifdef FI_BUILD_DLL
		#define FLICK_API __declspec(dllexport) 
	#else
		#define FLICK_API __declspec(dllimport)
	#endif 
#else 
	#define FLICK_API
#endif
#else
	#error Flick only supports Windows! 
#endif //FI only supports windows for now!

#ifdef FI_DEBUG
	#define FI_ENABLE_ASSERTS
#endif //enabling asserts for debug mode only


#ifdef FI_ENABLE_ASSERTS
	#define FI_ASSERT(x, ...) {if (!(x)) {FI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define FI_CORE_ASSERT(x, ...) {if (!(x)) {FI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define FI_ASSERT(x, ...)
	#define FI_CORE_ASSERT(x, ...)
#endif // assertions for when creating a glfw window


#define BIT(x) (1 << x)

#define FI_BIND_EVENT_FN(fn) std::bind(&ImGuiLayer::fn, this, std::placeholders::_1)  
