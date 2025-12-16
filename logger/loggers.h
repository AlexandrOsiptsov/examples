#ifndef LOGGERS_H
#define LOGGERS_H

#include "iface.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

#ifndef _WIN32
    #include <syslog.h>
#endif

// Консольный логгер с цветами (Linux/macOS)
class ConsoleLogger : public ILogger {
public:
    void log(LogLevel level, const std::string& message) override {
        std::ostringstream oss;
        oss << "[" << to_string(level) << "] " << message;

#ifndef _WIN32
        const char* color = "";
        switch (level) {
            case LogLevel::DEBUG:    color = "\033[36m"; break; // cyan
            case LogLevel::INFO:     color = "\033[32m"; break; // green
            case LogLevel::WARNING:  color = "\033[33m"; break; // yellow
            case LogLevel::ERROR:    color = "\033[31m"; break; // red
            case LogLevel::CRITICAL: color = "\033[41m\033[37m"; break;
        }
        std::cout << color << oss.str() << "\033[0m" << std::endl;
#else
        std::cout << oss.str() << std::endl;
#endif
    }
};

// Файловый логгер
class FileLogger : public ILogger {
    std::ofstream file;
public:
    explicit FileLogger(const std::string& filename) : file(filename.c_str()) {
        if (!this->file.is_open()) {
            std::cerr << "Cannot open log file: " << filename << std::endl;
        }
    }

    void log(LogLevel level, const std::string& message) override {
        if (!this->file.is_open()) return;

        std::time_t now = std::time(nullptr);
        char timebuf[100];
        std::strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

        this->file << timebuf << " [" << to_string(level) << "] " << message << std::endl;
        this->file.flush();
    }

    ~FileLogger() {
        if (this->file.is_open()) this->file.close();
    }
};

// Syslog (только Linux)
#ifdef __linux__
class SyslogLogger : public ILogger {
public:
    SyslogLogger() { openlog("CppLoggerApp", LOG_PID, LOG_USER); }
    ~SyslogLogger() { closelog(); }

    void log(LogLevel level, const std::string& message) override {
        int priority = LOG_INFO;
        switch (level) {
            case LogLevel::DEBUG:    priority = LOG_DEBUG; break;
            case LogLevel::INFO:     priority = LOG_INFO; break;
            case LogLevel::WARNING:  priority = LOG_WARNING; break;
            case LogLevel::ERROR:    priority = LOG_ERR; break;
            case LogLevel::CRITICAL: priority = LOG_CRIT; break;
        }
        syslog(priority, "%s", message.c_str());
    }
};
#endif

#endif // LOGGERS_H