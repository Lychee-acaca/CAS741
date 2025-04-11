/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/logger.hpp"

#include <chrono>  // NOLINT
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

static std::string getFormattedTimeString(const std::string& msg,
                                          const std::string& levelStr) {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
  std::tm local_tm = *std::localtime(&now_time_t);
  std::ostringstream oss;
  oss << std::put_time(&local_tm, "%H:%M:%S ");
  oss << "[" << levelStr << "] " << msg << "\n";
  return oss.str();
}

void Logger::log(std::string msg, LogLevel ll) {
  std::string combine_msg = getFormattedTimeString(msg, getLevelString(ll));

  if (logfile != nullptr) {
    *(logfile) << combine_msg;
    logfile->flush();
  }
  if (ll >= logLevel) {
    std::cout << combine_msg;
  }
}

void Logger::setLogPath(std::string filename) {
  if (logfile != nullptr) {
    logfile->close();
    delete logfile;
  }

  logfile = new std::ofstream(filename, std::ios::app);
  if (!logfile->is_open()) {
    std::cerr << "error creating logfile!" << std::endl;
    delete logfile;
  }
  log("Program started.", LogLevel::HIGH);
}
