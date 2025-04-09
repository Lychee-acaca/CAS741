/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/logger.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

std::string Logger::getLevelString(LogLevel ll) {
  switch (ll) {
    case LOW:
      return "LOW";
    case MEDIUM:
      return "MEDIUM";
    case HIGH:
      return "HIGH";
    default:
      return "UNKNOWN";
  }
}

void Logger::log(std::string msg, LogLevel ll) {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
  std::tm local_tm = *std::localtime(&now_time_t);
  if (ll >= logLevel) {
    std::cout << std::put_time(&local_tm, "%H:%M:%S ") << "["
              << getLevelString(ll) << "] " << msg << std::endl;
  }
  return;
}

void Logger::setLogPath(std::string filename) {
  this->log(filename);
  return;
}
