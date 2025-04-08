/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/logger.hpp"

#include <iostream>
#include <string>

void Logger::log(std::string msg, LogLevel ll) {
  if (ll >= logLevel) {
    std::cout << msg << std::endl;
  }
  return;
}

void Logger::setLogPath(std::string filename) {
  this->log(filename);
  return;
}
