/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/annRMSE.hpp"

#include <math.h>

float annRMSE_Solver::calRMSE(DoublyLL<int> *finalPeaks, DoublyLL<int> *ann) {
  auto fp_it = finalPeaks->begin();
  float sum = 0;
  int sum_cnt = 0;
  for (auto ap_it = ann->begin(); ap_it != ann->end(); ++ap_it) {
    if (fp_it == finalPeaks->end()) {
      break;
    }
    float min_dist = fabs(*(fp_it) - *(ap_it));
    auto fp_it_next = fp_it;
    ++fp_it_next;
    while (fp_it_next != finalPeaks->end() &&
           min_dist >= fabs(*(fp_it_next) - *(ap_it))) {
      ++fp_it;
      ++fp_it_next;
      min_dist = fabs(*(fp_it) - *(ap_it));
    }
    if (min_dist <= tolerance) {
      sum += min_dist * min_dist;
      ++sum_cnt;
    }
  }
  return sqrt(sum / sum_cnt);
}
