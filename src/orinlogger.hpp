#ifndef ORIN_LOGGER_HPP
#define ORIN_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace orin {

    enum level {
        all = -1,
        debug = 0,
        info = 1,
        warning = 2,
        error = 3,
        fatal = 4
    };

    class logger {
    private:
        const level minLevel;
        const char* logPrefixes[5];
        const char* logColors[5];

        const char *gettime() {
            static thread_local char buffer[20];

            using namespace std::chrono;

            auto now = system_clock::now();
            auto ms = duration_cast<milliseconds>(now.time_since_epoch());
            time_t t = ms.count() / 1000;

            int64_t totalSeconds = ms.count() / 1000;
            int seconds = totalSeconds % 60;
            int minutes = (totalSeconds / 60) % 60;
            int hours   = (totalSeconds / 3600) % 24;

            std::snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);
            return buffer;
        }

       void log(const char *message, level lvl) {
    if (lvl < minLevel) return;

    const char *prefix = logPrefixes[lvl];

    static char buffer[1024];
    int len = 0;

    #ifdef _WIN32
        SetConsoleTextAttribute(console, winColors[lvl]);
    #endif

    #ifdef ORIN_TIME_IMPLEMENTATION
        const char *time = gettime();

        #ifdef _WIN32
            constexpr const char* fmt = "[%s] [%s]: %s\n";
            len = std::snprintf(buffer, sizeof(buffer), fmt, time, prefix, message);
        #else
            constexpr const char* fmt = "%s[%s] [%s]: %s\033[0m\n";
            len = std::snprintf(buffer, sizeof(buffer), logColors[lvl], time, prefix, message);
        #endif

    #else
        #ifdef _WIN32
            constexpr const char* fmt = "[%s]: %s\n";
            len = std::snprintf(buffer, sizeof(buffer), prefix, message);
        #else
            constexpr const char* fmt = "%s[%s]: %s\033[0m\n";
            len = std::snprintf(buffer, sizeof(buffer), logColors[lvl], prefix, message);
        #endif
    #endif

    std::fwrite(buffer, 1, len, stdout);

    #ifdef _WIN32
        SetConsoleTextAttribute(console, 7);
    #endif
}


    public:
        logger(level minLevel) : minLevel(minLevel) {
            logPrefixes[level::debug] = "DEBUG";
            logPrefixes[level::info] = "INFO";
            logPrefixes[level::warning] = "WARNING";
            logPrefixes[level::error] = "ERROR";
            logPrefixes[level::fatal] = "FATAL";

            logColors[level::debug] = "\033[90m";
            logColors[level::info] = "\033[97m";
            logColors[level::warning] = "\033[93m";
            logColors[level::error] = "\033[91m";
            logColors[level::fatal] = "\033[91;1m";
        }

        inline void debug(const char* message) { log(message, level::debug); }
        inline void info(const char* message) { log(message, level::info); }
        inline void warn(const char* message) { log(message, level::warning); }
        inline void error(const char* message) { log(message, level::error); }
        inline void fatal(const char* message) { log(message, level::fatal); }

    };

    class LoggerIO {
    public:
        void writeLog(logger &logger, std::ostream &os);
        void readLog(std::istream &is);
    };


}

#endif
