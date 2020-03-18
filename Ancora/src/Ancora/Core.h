#pragma once

#ifdef AE_PLATFORM_WINDOWS
	#ifdef AE_BUILD_DLL
		#define ANCORA_API __declspec(dllexport)
	#else
		#define ANCORA_API __declspec(dllimport)
	#endif
#elif AE_PLATFORM_LINUX
	#ifdef AE_BUILD_DLL
		#define ANCORA_API __attribute__((visibility("default")))
	#else
		#define ANCORA_API 
	#endif
#else
	#error Ancora only supports Windows and Linux!
#endif

#define BIT(x) (1 << x)