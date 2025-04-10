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
  explicit GeneralDigitalFilter(DoublyLL<float> *b = nullptr,
                                DoublyLL<float> *a = nullptr)
      : b(b), a(a) {
    if (a) {
      regularize();
    }
  }

  void setParam(DoublyLL<float> *b = nullptr, DoublyLL<float> *a = nullptr) {
    this->b = b;
    this->a = a;
    regularize();
  }

  DoublyLL<float> *get_b(void) { return b; }
  DoublyLL<float> *get_a(void) { return a; }

  Signal *lfilter(Signal *x);

 private:
  DoublyLL<float> *b, *a;
  void regularize(void);
};
