/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#pragma once

#include "src/dataStructure.hpp"
#include "src/io_processing.hpp"

class GeneralDigitalFilter {
 public:
  explicit GeneralDigitalFilter(DoublyLL *b = nullptr, DoublyLL *a = nullptr)
      : b(b), a(a) {
    if (a) {
      regularize();
    }
  }

  void setParam(DoublyLL *b = nullptr, DoublyLL *a = nullptr) {
    this->b = b;
    this->a = a;
    regularize();
  }

  DoublyLL *get_b(void) { return b; }
  DoublyLL *get_a(void) { return a; }

  void lfilter(Signal *x, bool);

 private:
  DoublyLL *b, *a;
  void regularize(void);
};
