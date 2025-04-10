/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/mmath.hpp"

#include <math.h>

#include "src/logger.hpp"

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

Signal *MathFunc::calDiff(Signal *sig) {
  Signal *res = new Signal(sig->fs);
  float pre = 0;
  for (auto it = sig->signal->begin(); it != sig->signal->end(); ++it) {
    res->signal->push_back((*it) - pre);
    pre = (*it);
  }
  return res;
}

Signal *MathFunc::calNorm(Signal *sig, bool inplace) {
  Signal *res = nullptr;
  if (inplace) {
    res = sig;
  } else {
    res = new Signal(*sig);
  }
  float max_sig = -MMATH_FLOAT_INF;
  for (auto it = res->signal->begin(); it != res->signal->end(); ++it) {
    max_sig = MMATH_GET_MAX(max_sig, fabs(*it));
  }
  Logger::getInstance()->log("max_sig = " + std::to_string(max_sig));
  for (auto it = res->signal->begin(); it != res->signal->end(); ++it) {
    (*it) /= max_sig;
  }
  return res;
}

Signal *MathFunc::calMWI(Signal *sig, int windowSize) {
  Signal *res = new Signal(sig->fs);
  if (windowSize == -1) {
    windowSize = static_cast<int>(MMATH_DEFAULT_WINDOWSIZE_FACTOR * sig->fs);
  }
  Logger::getInstance()->log("windowSize = " + std::to_string(windowSize));

  int halfWindowSize = static_cast<int>(windowSize / 2);

  Signal *paddingSig = new Signal(*sig);
  for (int i = 0; i < halfWindowSize; ++i) {
    paddingSig->signal->push_head(0);
  }
  for (int i = 0; i < windowSize - halfWindowSize - 1; ++i) {
    paddingSig->signal->push_back(0);
  }

  float sum = 0;
  auto it_tail = paddingSig->signal->begin();
  auto it_head = paddingSig->signal->begin();

  for (int i = 0; i < windowSize; ++i) {
    if (it_tail == paddingSig->signal->end()) {
      break;
    }
    sum += *(it_tail++);
  }
  res->signal->push_back(sum / windowSize);

  while (it_tail != paddingSig->signal->end()) {
    sum += *(it_tail++);
    sum -= *(it_head++);
    res->signal->push_back(sum / windowSize);
  }

  delete paddingSig;
  return res;
}
