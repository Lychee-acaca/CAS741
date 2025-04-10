/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#pragma once

#include "src/io_processing.hpp"

class PanTompSolver {
 public:
  PanTompSolver()
      : rawSignal(nullptr),
        approxPeak(nullptr),
        mwiPeak(nullptr),
        rPeak(nullptr) {}
  DoublyLL<int> *findPeak(Signal *);

 private:
  void findApproxPeak(void);
  void calMWIPeak(void);
  void refineRPeaksOnRawSignal(int = 300);

  Signal *rawSignal;
  Signal *MWI2Signal;
  DoublyLL<int> *approxPeak;
  DoublyLL<int> *mwiPeak;
  DoublyLL<int> *rPeak;
};
