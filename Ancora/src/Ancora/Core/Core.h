#pragma once

#include <memory>

#ifdef AE_PLATFORM_WINDOWS
	#ifdef AE_DYNAMIC_LINK
		#ifdef AE_BUILD_DLL
			#define ANCORA_API __declspec(dllexport)
		#else
			#define ANCORA_API __declspec(dllimport)
		#endif
	#else
		#define ANCORA_API
	#endif
#elif AE_PLATFORM_LINUX
	#ifdef AE_DYNAMIC_LINK
		#ifdef AE_BUILD_DLL
			#define ANCORA_API __attribute__((visibility("default")))
		#else
			#define ANCORA_API
		#endif
	#else
		#define ANCORA_API
	#endif
#else
	#error Ancora only supports Windows and Linux!
#endif


#define BIT(x) (1 << x)

#define AE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Ancora {

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
