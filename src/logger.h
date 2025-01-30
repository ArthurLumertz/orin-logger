#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <istream>

namespace logger {

	typedef enum {
		DEBUG,
		WARNING,
		INFO,
		ERROR,
		FATAL,
	} Level;

	void setLogLevel(const Level level);
	void usePrimaryThread(bool usePrimary);

	void info(const std::string& message);
	void debug(const std::string& message);
	void warn(const std::string& message);
	void error(const std::string& message);
	void fatal(const std::string& message);

	const std::vector<std::string> getFullLog();
	
	void writeLog(std::ostream& outputStream);
	void readLog(std::istream& inputStream);

}