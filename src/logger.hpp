/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#pragma once

#include <string>

class Logger {
 public:
  enum LogLevel { LOW, MEDIUM, HIGH };
  static Logger *getInstance(void) {
    static Logger instance;
    return &instance;
  }
  void log(std::string, LogLevel);
  void setLogLevel(LogLevel ll) { logLevel = ll; }
  void setLogPath(std::string);

 private:
  Logger(void) : logLevel(LogLevel::MEDIUM) {}
  LogLevel logLevel;
};
