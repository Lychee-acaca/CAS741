/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/mmath.hpp"

Signal *MathFunc::calSquare(Signal *sig, bool inplace) {
  Signal *res = nullptr;
  if (inplace) {
    res = sig;
  } else {
    res = new Signal(*sig);
  }
  for (auto it = res->signal->begin(); it != res->signal->end(); ++it) {
    (*it) = (*it) * (*it);
  }
  return res;
}
