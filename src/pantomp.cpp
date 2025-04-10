/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/pantomp.hpp"

#include <cassert>

#include "src/generalDigitalFilter.hpp"
#include "src/logger.hpp"
#include "src/mmath.hpp"

Signal *LPF(Signal *sig) {
  DoublyLL<float> *b = new DoublyLL<float>();
  DoublyLL<float> *a = new DoublyLL<float>();

  b->push_back(6.68607912e-05);
  b->push_back(2.67443165e-04);
  b->push_back(4.01164747e-04);
  b->push_back(2.67443165e-04);
  b->push_back(6.68607912e-05);

  a->push_back(1.0f);
  a->push_back(-3.49868423f);
  a->push_back(4.61791585f);
  a->push_back(-2.72312355f);
  a->push_back(0.60496169f);

  GeneralDigitalFilter *gdf = new GeneralDigitalFilter(b, a);
  auto out = gdf->lfilter(sig);

  delete gdf;
  delete b;
  delete a;

  return out;
}

Signal *HPF(Signal *sig) {
  DoublyLL<float> *b = new DoublyLL<float>();
  DoublyLL<float> *a = new DoublyLL<float>();

  b->push_back(0.89220304f);
  b->push_back(-3.56881217f);
  b->push_back(5.35321825f);
  b->push_back(-3.56881217f);
  b->push_back(0.89220304f);

  a->push_back(1.0f);
  a->push_back(-3.77199675f);
  a->push_back(5.341624f);
  a->push_back(-3.36560165f);
  a->push_back(0.79602627f);

  GeneralDigitalFilter *gdf = new GeneralDigitalFilter(b, a);
  auto out = gdf->lfilter(sig);

  delete gdf;
  delete b;
  delete a;

  return out;
}

DoublyLL<int> *PanTompSolver::findPeak(Signal *rawSignal) {
  this->rawSignal = rawSignal;

  Signal *sig_LPF = LPF(rawSignal);
  Signal *sig_HPF = HPF(sig_LPF);
  Signal *sig_norm = MathFunc::calNorm(sig_HPF, true);
  Signal *sig_diff = MathFunc::calDiff(sig_norm);
  Signal *sig_square = MathFunc::calSquare(sig_diff, true);
  Signal *sig_MWI = MathFunc::calMWI(sig_square);
  MWI2Signal = MathFunc::calMWI(sig_MWI, 25);

  delete sig_LPF;
  delete sig_norm;
  delete sig_square;
  delete sig_MWI;

  findApproxPeak();
  calMWIPeak();
  refineRPeaksOnRawSignal();

  delete MWI2Signal;
  delete approxPeak;
  delete mwiPeak;

  return rPeak;
}

void PanTompSolver::findApproxPeak(void) {
  assert(MWI2Signal != nullptr);
  approxPeak = new DoublyLL<int>();
  if (MWI2Signal->signal->getLen() < 3) {
    return;
  }
  auto it = MWI2Signal->signal->begin();
  float p1 = *(it++);
  float p2 = *(it++);
  int cnt = 1;
  for (; it != MWI2Signal->signal->end(); ++it) {
    if (p1 <= p2 && p2 >= *(it)) {
      approxPeak->push_back(cnt);
    }
    p1 = p2;
    p2 = *(it);
    ++cnt;
  }
}

void PanTompSolver::calMWIPeak(void) {
  assert(approxPeak != nullptr);
  mwiPeak = new DoublyLL<int>();
  if (approxPeak->getLen() < 8) {
    Logger::getInstance()->log("Not enough peaks to initialize thresholds!",
                               Logger::LogLevel::HIGH);
    return;
  }
  float SPKF = 0, NPKF = 0;

  auto aPeaks_it = approxPeak->begin();
  for (int i = 0; i < 4; ++i) {
    SPKF += MWI2Signal->signal->getIndex(*(aPeaks_it++))->getData();
  }
  for (int i = 4; i < 8; ++i) {
    NPKF += MWI2Signal->signal->getIndex(*(aPeaks_it++))->getData();
  }
  SPKF /= 4.0;
  NPKF /= 4.0;

  float THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);

  int last_qrs_index = -MMATH_FLOAT_INF;
  int RR_missed_limit = static_cast<int>(1.66 * MWI2Signal->fs);

  auto signal_it = MWI2Signal->signal->begin();
  int pre_peak = 0;
  for (aPeaks_it = approxPeak->begin(); aPeaks_it != approxPeak->end();
       ++aPeaks_it) {
    int peak = *aPeaks_it;
    for (int i = 0; i < peak - pre_peak; ++i) {
      ++signal_it;
    }
    float peak_val = *(signal_it);
    pre_peak = peak;

    if (peak_val > THRESHOLD1) {
      mwiPeak->push_back(peak);
      SPKF = 0.125 * peak_val + 0.875 * SPKF;
      last_qrs_index = peak;
    } else {
      NPKF = 0.125 * peak_val + 0.875 * NPKF;
    }

    THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
    float THRESHOLD2 = 0.5 * THRESHOLD1;

    if ((peak - last_qrs_index > RR_missed_limit) && (peak_val > THRESHOLD2)) {
      mwiPeak->push_back(peak);
      SPKF = 0.25 * peak_val + 0.75 * SPKF;
      last_qrs_index = peak;
      THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
    }
  }
}

void PanTompSolver::refineRPeaksOnRawSignal(int windowMs) {
  rPeak = new DoublyLL<int>();
  int half_window = static_cast<int>((windowMs * rawSignal->fs) / 1000 / 2);

  auto sig_it = rawSignal->signal->begin();
  int pre_roughPeak = 0;
  for (auto it = mwiPeak->begin(); it != mwiPeak->end(); ++it) {
    int roughPeak = *(it);
    for (int i = 0; i < roughPeak - pre_roughPeak; ++i) {
      ++sig_it;
    }
    pre_roughPeak = roughPeak;
    int start = MMATH_GET_MAX(0, roughPeak - half_window);
    int end = MMATH_GET_MIN(static_cast<int>(rawSignal->signal->getLen()) - 1,
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
    rPeak->push_back(max_idx);
  }
}
