#ifndef IFACE_H
#define IFACE_H

#include <string>
#include <vector>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

inline const char* to_string(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO ";
        case LogLevel::WARNING:  return "WARN ";
        case LogLevel::ERROR:    return "ERROR";
        case LogLevel::CRITICAL: return "CRIT ";
    }
    return "?????";
}

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(LogLevel level, const std::string& message) = 0;

    void debug(const std::string& msg)    { log(LogLevel::DEBUG,    msg); }
    void info(const std::string& msg)     { log(LogLevel::INFO,     msg); }
    void warning(const std::string& msg)  { log(LogLevel::WARNING,  msg); }
    void error(const std::string& msg)    { log(LogLevel::ERROR,    msg); }
    void critical(const std::string& msg) { log(LogLevel::CRITICAL, msg); }
};

class GLogger {
private:
    static inline std::vector<ILogger*> loggers;

public:
    static void add(ILogger* logger) {
        if (logger) loggers.push_back(logger);
    }

    static void log(LogLevel level, const std::string& message) {
        for (auto logger : loggers) {
            if (logger) logger->log(level, message);
        }
    }

    static void debug(const std::string& msg)    { log(LogLevel::DEBUG,    msg); }
    static void info(const std::string& msg)     { log(LogLevel::INFO,     msg); }
    static void warning(const std::string& msg)  { log(LogLevel::WARNING,  msg); }
    static void error(const std::string& msg)    { log(LogLevel::ERROR,    msg); }
    static void critical(const std::string& msg) { log(LogLevel::CRITICAL, msg); }
};

#endif // IFACE_H