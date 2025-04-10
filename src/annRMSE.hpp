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

class annRMSE_Solver {
 public:
  explicit annRMSE_Solver(int tolerance = 100) : tolerance(tolerance) {}
  float calRMSE(DoublyLL<int> *, DoublyLL<int> *);

 private:
  int tolerance;
};
