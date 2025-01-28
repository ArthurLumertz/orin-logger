#define LOGGER_EXPORTS
#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define MAX_LOGS			100000
#define LOG_BUFFER_SIZE		256
#define ALL_LOGS_SIZE		(MAX_LOGS * LOG_BUFFER_SIZE)

static char all_logs[ALL_LOGS_SIZE];
static char log_buffer[MAX_LOGS][LOG_BUFFER_SIZE];
static int log_index = 0;

#define RESET_COLOR "\033[0m"
#define WHITE_COLOR "\033[97m"
#define GRAY_COLOR "\033[37m"
#define YELLOW_COLOR "\033[93m"
#define RED_COLOR "\033[91m"
#define DARK_RED_COLOR "\033[38;5;1m"

const char* get_current_time() {
	time_t t;
	struct tm tm_info;
	static char time_str[20];

	time(&t);
	localtime_s(&tm_info, &t);
	strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);
	
	return time_str;
}

const char* get_color_for_level(int level) {
	switch (level) {
		case LOG_INFO: return WHITE_COLOR;
		case LOG_DEBUG: return GRAY_COLOR;
		case LOG_WARNING: return YELLOW_COLOR;
		case LOG_ERROR: return RED_COLOR;
		case LOG_FATAL: return DARK_RED_COLOR;
		default: return RESET_COLOR;
	}
}

void LOGGER_log(const LogLevel level, LOGGER_char message, va_list args) {
	if (log_index >= MAX_LOGS) return;

	const char* level_str;
	const char* color_code = get_color_for_level(level);

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

	snprintf(log_buffer[log_index], LOG_BUFFER_SIZE, "%s[%s] [%s]: %s%s", color_code, get_current_time(), level_str, formatted_message, RESET_COLOR);

	errno_t err = strncat_s(all_logs, ALL_LOGS_SIZE, log_buffer[log_index], ALL_LOGS_SIZE - strlen(all_logs) - 1);
    if (err != 0) {
        LOGGER_fatal("Error appending log message.");
    }

	printf("%s\n", log_buffer[log_index]);
	log_index++;
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