#define LOGGER_EXPORTS
#include "logger.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

const char* get_current_time() {
	time_t t;
	struct tm tm_info;
	static char time_str[20];

	time(&t);
	localtime_s(&tm_info, &t);
	strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);
	
	return time_str;
}

void LOGGER_log(const LogLevel level, LOGGER_char message) {
	const char* level_str;

	switch (level) {
		case LOG_INFO: level_str = "INFO"; break;
		case LOG_DEBUG: level_str = "DEBUG"; break;
		case LOG_WARNING: level_str = "WARNING"; break;
		case LOG_ERROR: level_str = "ERROR"; break;
		case LOG_FATAL: level_str = "FATAL"; break;
		default: level_str = "UNKNOWN"; break;
	}

	printf("[%s] [%s]: %s\n", get_current_time(), level_str, message);
}

void LOGGER_info(LOGGER_char message) {
	LOGGER_log(LOG_INFO, message);
}

void LOGGER_debug(LOGGER_char message) {
	LOGGER_log(LOG_DEBUG, message);
}

void LOGGER_warning(LOGGER_char message) {
	LOGGER_log(LOG_WARNING, message);
}

void LOGGER_error(LOGGER_char message) {
	LOGGER_log(LOG_ERROR, message);
}

void LOGGER_fatal(LOGGER_char message) {
	LOGGER_log(LOG_FATAL, message);
}