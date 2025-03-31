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

class MathFunc {
 public:
  static Signal *calSquare(Signal *, bool = false);
  static Signal *calThreshold(const Signal *, float th);
  static Signal *calRMSE(const Signal *, const Signal *);
};
