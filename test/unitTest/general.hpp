/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#pragma once

#include <gtest/gtest.h>
#include <math.h>

#include <fstream>
#include <string>

#define FLOAT_TOLERANCE (0.00001f)

class General {
 public:
  template <typename T>
  static int readSeqData(std::ifstream &infile, DoublyLL<T> *data) {
    int len = 0;
    if (!(infile >> len)) {
      std::cerr << "Failed to read the length." << std::endl;
      return 1;
    }
    for (int i = 0; i < len; ++i) {
      float val;
      if (!(infile >> val)) {
        std::cerr << "Failed to read value " << i + 1 << std::endl;
        return 1;
      }
      data->push_back(val);
    }
    return 0;
  }

  template <typename T>
  static float RMSE(DoublyLL<T> *x, DoublyLL<T> *y) {
    EXPECT_EQ(x->getLen(), y->getLen());

    auto x_it = x->begin();
    auto y_it = y->begin();
    float sum = 0;
    for (; x_it != x->end(); ++x_it, ++y_it) {
      sum += std::pow((*x_it) - (*y_it), 2.0);
    }
    return sum /= x->getLen();
  }
};
