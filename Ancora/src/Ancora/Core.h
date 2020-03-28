#pragma once

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
