#pragma once

#ifdef SHELL_PLATFORM_WINDOWS
	#ifdef SHELL_BUILD_DLL
		#define SHELL_API __declspec(dllexport)
	#else
		#define SHELL_API __declspec(dllimport)
	#endif // SHELL_BUILD_DLL
#endif // SHELL_PLATFORM_WINDOWS

