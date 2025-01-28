#ifndef LOGGER_H
#define LOGGER_H

#ifdef _WIN32
	#ifdef LOGGER_EXPORTS
		#define LOGGER_API __declspec(dllexport)
	#else
		#define LOGGER_API __declspec(dllimport)
	#endif
#else
	#ifdef LOGGER_EXPORTS
		#define LOGGER_API __attribute__((visibility("default")))
	#else
		#define LOGGER_API
	#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_DEBUG,
	LOG_FATAL,
} LogLevel;

typedef const char* LOGGER_char;

LOGGER_API void LOGGER_log(const LogLevel level, const char* message);

LOGGER_API void LOGGER_info(LOGGER_char message);
LOGGER_API void LOGGER_debug(LOGGER_char message);
LOGGER_API void LOGGER_warning(LOGGER_char message);
LOGGER_API void LOGGER_error(LOGGER_char message);
LOGGER_API void LOGGER_fatal(LOGGER_char message);

#ifdef __cplusplus
}
#endif

#endif