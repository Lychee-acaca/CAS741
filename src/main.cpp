#include <iostream>
#include "logger.hpp"

int main()
{
    Logger logger;
    logger.log("Hello", Logger::LogLevel::HIGH);
    return 0;
}