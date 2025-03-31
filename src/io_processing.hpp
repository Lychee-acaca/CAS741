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

#include "src/dataStructure.hpp"

class Signal {
 public:
  DoublyLL signal;
  int fs;
};

class IO_Processing {
 public:
  IO_Processing(void) {}
  Signal *readFromFile(std::string);
};
