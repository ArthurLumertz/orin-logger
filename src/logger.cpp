#include "logger.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <cstdio>
#include <thread>
#include <mutex>
#include <stdexcept>

#define RESET_COLOR		"\033[0m"
#define GRAY_COLOR		"\033[38;2;150;150;150m"
#define YELLOW_COLOR	"\033[93m"
#define RED_COLOR		"\033[91m"
#define DARK_RED_COLOR	"\033[38;5;1m"

#define MAX_BUFFER_SIZE	1024

namespace logger {

	static Level m_minLevel;

	static std::mutex m_mutex;
	static bool m_usePrimaryThread;

	static std::vector<std::string> m_log;
	
	void setLogLevel(const Level level) {
		m_minLevel = level;
	}

	void usePrimaryThread(bool usePrimary) {
		m_usePrimaryThread = usePrimary;
	}

	static std::string getCurrentTime() {
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		char buffer[100];

		std::tm tmPtr;
		#if defined(_MSC_VER)
			localtime_s(&tmPtr, &time);
		#else
			tmPtr = *std::localtime(&time);
		#endif

		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tmPtr);
		return std::string(buffer);
	}

	static const char* getColor(const Level level) {
		switch (level) {
		//case INFO: return WHITE_COLOR;
		case DEBUG: return GRAY_COLOR;
		case WARNING: return YELLOW_COLOR;
		case ERROR: return RED_COLOR;
		case FATAL: return DARK_RED_COLOR;
		default: return RESET_COLOR;
		}
	}

	static void threadedLog(const std::string& message, const Level level) {
		if (level >= m_minLevel) {
			if (message.size() > MAX_BUFFER_SIZE) {
				throw std::runtime_error("Message size surpassed MAX_BUFFER_SIZE(1024)");
			}

			const char* logLevel = "INFO";
			switch (level) {
			case INFO: logLevel = "INFO"; break;
			case DEBUG: logLevel = "DEBUG"; break;
			case WARNING: logLevel = "WARNING"; break;
			case FATAL: logLevel = "FATAL"; break;
			}

			char formatted_message[MAX_BUFFER_SIZE];
			snprintf(formatted_message, sizeof(formatted_message), "%s[%s] [%s]: %s%s", getColor(level), getCurrentTime().c_str(), logLevel, message.c_str(), RESET_COLOR);
			
			std::lock_guard<std::mutex> lock(m_mutex);

			printf("%s%s\n", formatted_message, RESET_COLOR);
			m_log.push_back("[" + getCurrentTime() + "] [" + logLevel + "]: " + message.c_str());
		}

	}

	static void log(const std::string& message, const Level level) {
		if (!m_usePrimaryThread) {
			std::thread logThread(threadedLog, message, level);
			logThread.join();
			return;
		}

		if (level >= m_minLevel) {
			if (message.size() > MAX_BUFFER_SIZE) {
				// throw exception
				return;
			}

			const char* logLevel = "INFO";
			switch (level) {
			case INFO: logLevel = "INFO"; break;
			case DEBUG: logLevel = "DEBUG"; break;
			case WARNING: logLevel = "WARNING"; break;
			case FATAL: logLevel = "FATAL"; break;
			}

			char formatted_message[MAX_BUFFER_SIZE];
			snprintf(formatted_message, sizeof(formatted_message), "%s[%s] [%s]: %s%s", getColor(level), getCurrentTime().c_str(), logLevel, message.c_str(), RESET_COLOR);

			std::lock_guard<std::mutex> lock(m_mutex);

			printf("%s%s\n", formatted_message, RESET_COLOR);
			m_log.push_back("[" + getCurrentTime() + "] [" + logLevel + "]: " + message.c_str());
		}
	}

	void info(const std::string& message) {
		log(message, INFO);
	}

	void debug(const std::string& message) {
		log(message, DEBUG);
	}

	void warn(const std::string& message) {
		log(message, WARNING);
	}

	void error(const std::string& message) {
		log(message, ERROR);
	}

	void fatal(const std::string& message) {
		log(message, FATAL);
	}

	const std::vector<std::string> getFullLog() {
		return m_log;
	}

	void writeLog(std::ostream& outputStream) {
		for (const auto& entry : m_log) {
			outputStream << entry << std::endl;
		}
	}

	void readLog(std::istream& inputStream) {
		std::string line;
		m_log.clear();
		while (std::getline(inputStream, line)) {
			m_log.push_back(line);
		}
	}

}