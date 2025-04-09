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

DoublyLL *MathFunc::findApproxPeak(Signal *sig) {
  DoublyLL *res = new DoublyLL();
  if (sig->signal->getLen() < 3) {
    return res;
  }
  auto it = sig->signal->begin();
  float p1 = *(it++);
  float p2 = *(it++);
  int cnt = 1;
  for (; it != sig->signal->end(); ++it) {
    if (p1 <= p2 && p2 >= *(it)) {
      res->push_back(cnt);
    }
    p1 = p2;
    p2 = *(it);
    ++cnt;
  }
  return res;
}

// TODO(Jared): DoublyLL要改成模板类，索引不应该使用int类型

DoublyLL *MathFunc::calThreshold(Signal *sig, DoublyLL *aPeaks) {
  DoublyLL *res = new DoublyLL();
  if (aPeaks->getLen() < 8) {
    Logger::getInstance()->log("Not enough peaks to initialize thresholds!",
                               Logger::LogLevel::HIGH);
    return res;
  }
  float SPKF = 0, NPKF = 0;

  auto aPeaks_it = aPeaks->begin();
  for (int i = 0; i < 4; ++i) {
    SPKF += sig->signal->getIndex(*(aPeaks_it++))->getData();
  }
  for (int i = 4; i < 8; ++i) {
    NPKF += sig->signal->getIndex(*(aPeaks_it++))->getData();
  }
  SPKF /= 4.0;
  NPKF /= 4.0;

  float THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);

  int last_qrs_index = -1e9;
  int RR_missed_limit = static_cast<int>(1.66 * sig->fs);

  auto signal_it = sig->signal->begin();
  int pre_peak = 0;
  for (aPeaks_it = aPeaks->begin(); aPeaks_it != aPeaks->end(); ++aPeaks_it) {
    int peak = *aPeaks_it;
    for (int i = 0; i < peak - pre_peak; ++i) {
      ++signal_it;
    }
    float peak_val = *(signal_it);
    pre_peak = peak;

    if (peak_val > THRESHOLD1) {
      res->push_back(peak);
      SPKF = 0.125 * peak_val + 0.875 * SPKF;
      last_qrs_index = peak;
    } else {
      NPKF = 0.125 * peak_val + 0.875 * NPKF;
    }

    THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
    float THRESHOLD2 = 0.5 * THRESHOLD1;

    if ((peak - last_qrs_index > RR_missed_limit) && (peak_val > THRESHOLD2)) {
      res->push_back(peak);
      SPKF = 0.25 * peak_val + 0.75 * SPKF;
      last_qrs_index = peak;
      THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
    }
  }

  return res;
}

DoublyLL *MathFunc::refineRPeaksOnRawSignal(Signal *sig, DoublyLL *roughPeaks,
                                            int windowMs) {
  DoublyLL *res = new DoublyLL();
  int half_window = static_cast<int>((windowMs * sig->fs) / 1000 / 2);

  auto sig_it = sig->signal->begin();
  int pre_roughPeak = 0;
  for (auto it = roughPeaks->begin(); it != roughPeaks->end(); ++it) {
    int roughPeak = *(it);
    for (int i = 0; i < roughPeak - pre_roughPeak; ++i) {
      ++sig_it;
    }
    pre_roughPeak = roughPeak;
    int start = MMATH_GET_MAX(0, roughPeak - half_window);
    int end = MMATH_GET_MIN(static_cast<int>(sig->signal->getLen()) - 1,
                            roughPeak + half_window);
    auto sig_it2 = sig_it;
    for (int i = roughPeak; i > start; --i) {
      --sig_it2;
    }

    double max_val = *(sig_it2);
    int max_idx = start;
    for (int i = start + 1; i <= end; ++i) {
      if (*(++sig_it2) > max_val) {
        max_val = *(sig_it2);
        max_idx = i;
      }
    }
    res->push_back(max_idx);
  }

  return res;
}
