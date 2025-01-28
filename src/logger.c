#define LOGGER_EXPORTS
#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define MAX_LOGS		100000
#define LOG_BUFFER_SIZE	256
#define ALL_LOGS_SIZE (MAX_LOGS * LOG_BUFFER_SIZE)

static char all_logs[ALL_LOGS_SIZE];
static char log_buffer[MAX_LOGS][LOG_BUFFER_SIZE];
static int log_index = 0;

const char* get_current_time() {
	time_t t;
	struct tm tm_info;
	static char time_str[20];

	time(&t);
	localtime_s(&tm_info, &t);
	strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);
	
	return time_str;
}

void LOGGER_log(const LogLevel level, LOGGER_char message, va_list args) {
	if (log_index < MAX_LOGS) {
		const char* level_str;

		switch (level) {
		case LOG_INFO: level_str = "INFO"; break;
		case LOG_DEBUG: level_str = "DEBUG"; break;
		case LOG_WARNING: level_str = "WARNING"; break;
		case LOG_ERROR: level_str = "ERROR"; break;
		case LOG_FATAL: level_str = "FATAL"; break;
		default: level_str = "UNKNOWN"; break;
		}

		char formatted_message[LOG_BUFFER_SIZE];

		vsnprintf(formatted_message, sizeof(formatted_message), message, args);

		snprintf(log_buffer[log_index], LOG_BUFFER_SIZE, "[%s] [%s]: %s", get_current_time(), level_str, formatted_message);

		log_index++;
	}

	printf("%s\n", log_buffer[log_index - 1]);
}

void LOGGER_info(LOGGER_char message, ...) {
	va_list args;
	va_start(args, message);
	LOGGER_log(LOG_INFO, message, args);
	va_end(args);
}

void LOGGER_debug(LOGGER_char message, ...) {
	va_list args;
	va_start(args, message);
	LOGGER_log(LOG_DEBUG, message, args);
	va_end(args);
}

void LOGGER_warning(LOGGER_char message, ...) {
	va_list args;
	va_start(args, message);
	LOGGER_log(LOG_WARNING, message, args);
	va_end(args);
}

void LOGGER_error(LOGGER_char message, ...) {
	va_list args;
	va_start(args, message);
	LOGGER_log(LOG_ERROR, message, args);
	va_end(args);
}

void LOGGER_fatal(LOGGER_char message, ...) {
	va_list args;
	va_start(args, message);
	LOGGER_log(LOG_FATAL, message, args);
	va_end(args);
}

const char* LOGGER_logs(void) {
	memset(all_logs, 0, sizeof(all_logs));

	for (size_t i = 0; i < log_index; i++) {
		if (strcat_s(all_logs, ALL_LOGS_SIZE, log_buffer[i]) != 0) {
			LOGGER_fatal("Error appending log message.");
			break;
		}
		if (strcat_s(all_logs, ALL_LOGS_SIZE, "\n") != 0) {
			LOGGER_fatal("Error appending newline.");
			break;
		}
	}
	
	return all_logs;
}

void LOGGER_write(const char* filepath) {
	FILE* file = NULL;

	errno_t err = fopen_s(&file, filepath, "w");
	if (err != 0 || !file) {
		LOGGER_fatal("Error opening file for writing.");
		return;
	}

	const char* logs = LOGGER_logs();
	if (fputs(logs, file) == EOF) {
		LOGGER_fatal("Error writing logs to file");
	}

	fclose(file);
}