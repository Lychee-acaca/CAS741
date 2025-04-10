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

#define MMATH_GET_MAX(A, B) ((A) > (B) ? (A) : (B))
#define MMATH_GET_MIN(A, B) ((A) < (B) ? (A) : (B))
#define MMATH_FLOAT_INF (1.0E9f)
#define MMATH_DEFAULT_WINDOWSIZE_FACTOR (0.150f)

class MathFunc {
 public:
  static Signal *calSquare(Signal *, bool = false);
  static Signal *calDiff(Signal *);
  static Signal *calNorm(Signal *, bool = false);
  static Signal *calMWI(Signal *, int = -1);
  static Signal *calRMSE(const Signal *, const Signal *);
};
