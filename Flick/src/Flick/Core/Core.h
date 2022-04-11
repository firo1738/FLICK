#pragma once

#include <memory>

//Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64 */
		#define FI_PLATFORM_WINDOWS
	#else 
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || (__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define FI_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define FI_PLATFORM_MACOS
		#error "MACOS is not supported!"
	#else 
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel 
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define FI_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define FI_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif //End of platform detection


//DLL support
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
#endif //End of DLL support

#ifdef FI_DEBUG
	#define FI_ENABLE_ASSERTS
#endif //enabling asserts for debug mode only

//TODO:: make this macro take only condition, no other arguments
#ifdef FI_ENABLE_ASSERTS
	#define FI_ASSERT(x, ...) {if (!(x)) {FI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define FI_CORE_ASSERT(x, ...) {if (!(x)) {FI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define FI_ASSERT(x, ...)
	#define FI_CORE_ASSERT(x, ...)
#endif // assertions for when creating a glfw window


#define BIT(x) (1 << x)

#define FI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)  

namespace Flick
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}