#pragma once

#include <string>

class Logger
{
    public:
        enum LogLevel
        {
            LOW,
            MEDIUM,
            HIGH
        };
        Logger(LogLevel ll=LogLevel::MEDIUM) : logLevel(ll) {};
        void log(std::string, LogLevel);
        void setLogLevel(LogLevel ll) {logLevel = ll;};
        void setLogPath(std::string);
    private:
        LogLevel logLevel;

};
