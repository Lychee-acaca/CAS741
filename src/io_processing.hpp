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
  explicit Signal(int fs = 0) : signal(new DoublyLL()), fs(fs) {}
  explicit Signal(const Signal &s)
      : signal(new DoublyLL(*(s.signal))), fs(s.fs) {}
  DoublyLL *signal;
  int fs;
};

class IO_Processing {
 public:
  static Signal *readFromFile(const std::string);
  static void writeToFile(const std::string, DoublyLL *);
  static void writeToFile(const std::string, Signal *);
};
