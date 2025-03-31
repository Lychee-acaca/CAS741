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
  explicit Logger(LogLevel ll = LogLevel::MEDIUM) : logLevel(ll) {}
  void log(std::string, LogLevel);
  void setLogLevel(LogLevel ll) { logLevel = ll; }
  void setLogPath(std::string);

 private:
  LogLevel logLevel;
};
