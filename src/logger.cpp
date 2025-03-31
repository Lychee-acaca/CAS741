#include "logger.hpp"
#include <iostream>

void Logger::log(std::string msg, LogLevel ll=LogLevel::LOW)
{
    if (ll >= logLevel)
    {
        std::cout << msg << std::endl;
    }
    return;
}

void Logger::setLogPath(std::string filename)
{
    this->log(filename);
    return;
}
