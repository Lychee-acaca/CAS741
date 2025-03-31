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
  DoublyLL_Node *now = res->signal->getIndex(0);
  while (now != nullptr) {
    now->setData(now->getData() * now->getData());
    now = now->getNext();
  }
  return res;
}
