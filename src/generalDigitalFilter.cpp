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

Signal *GeneralDigitalFilter::lfilter(Signal *x) {
  Signal *res = new Signal(x->fs);

  int cnt = 0;
  // Time complexity can be optimized
  for (auto it = x->signal->begin(); it != x->signal->end(); ++it) {
    float sum = 0;

    auto xx = it;
    for (int i = 0; i < b->getLen(); ++i) {
      if (cnt - i >= 0) {
        sum += b->getIndex(i)->getData() * (*(xx--));
      }
    }

    for (int i = 1; i < a->getLen(); ++i) {
      if (cnt - i >= 0) {
        sum -= a->getIndex(i)->getData() *
               res->signal->getIndex(cnt - i)->getData();
      }
    }

    res->signal->push_back(sum);
    ++cnt;
  }

  return res;
}

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
