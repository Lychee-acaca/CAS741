/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include <iostream>

#include "src/dataStructure.hpp"
#include "src/logger.hpp"

int main() {
  Logger::getInstance()->log("Hello", Logger::LogLevel::HIGH);

  return 0;
}
