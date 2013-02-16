#ifndef CONFIG_H
#define CONFIG_H

#if defined(_WIN64)
	#define OS_WINDOWS
	#define OS_WINDOWS_64
#elif defined(_WIN32)
	#define OS_WINDOWS
	#define OS_WINDOWS_32
#elif defined(__APPLE__)
	#define OS_APPLE
#elif defined(__ANDROID__)
	#define OS_ANDROID
#elif defined(__linux)
    #define OS_LINUX
    #define OS_UNIX
#elif defined(__unix)
    #define OS_UNIX
#else
	#define OS_UNKNOWN
#endif

#endif
