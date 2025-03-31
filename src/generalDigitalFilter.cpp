/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/generalDigitalFilter.hpp"

#include <cassert>

void GeneralDigitalFilter::lfilter(Signal *x, bool inplace) {}

void GeneralDigitalFilter::regularize(void) {
  assert(a->getLen() >= 1);
  for (auto it = b->begin(); it != b->end(); ++it) {
    (*it) = (*it) / *(a->begin());
  }
  for (auto it = ++(a->begin()); it != a->end(); ++it) {
    (*it) = (*it) / *(a->begin());
  }
  *(a->begin()) = 1;
}
