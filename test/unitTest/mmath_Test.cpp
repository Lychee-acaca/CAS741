/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/mmath.hpp"

#include <gtest/gtest.h>

#include "src/dataStructure.hpp"
#include "test/unitTest/general.hpp"

TEST(Math_Test, calSquare) {
  Signal *sig = new Signal();
  sig->signal->push_back(1.2f);
  sig->signal->push_back(-2.1f);
  sig->signal->push_back(-1.0f);
  sig->signal->push_back(2.0f);
  sig->signal->push_back(3.0f);

  Signal *sig_square = MathFunc::calSquare(sig);

  EXPECT_NEAR(sig_square->signal->getIndex(0)->getData(), 1.44f,
              FLOAT_TOLERANCE);
  EXPECT_NEAR(sig_square->signal->getIndex(1)->getData(), 4.41f,
              FLOAT_TOLERANCE);
  EXPECT_NEAR(sig_square->signal->getIndex(2)->getData(), 1.0f,
              FLOAT_TOLERANCE);
  EXPECT_NEAR(sig_square->signal->getIndex(3)->getData(), 4.0f,
              FLOAT_TOLERANCE);
  EXPECT_NEAR(sig_square->signal->getIndex(4)->getData(), 9.0f,
              FLOAT_TOLERANCE);

  EXPECT_EQ(sig_square->signal->getIndex(4)->getNext(), nullptr);

  delete sig_square;

  delete sig;
}

TEST(Math_Test, calSquare_inplace) {
  Signal *sig = new Signal();
  sig->signal->push_back(1.2f);
  sig->signal->push_back(-2.1f);
  sig->signal->push_back(-1.0f);
  sig->signal->push_back(2.0f);
  sig->signal->push_back(3.0f);

  Signal *sig_square = MathFunc::calSquare(sig, true);

  EXPECT_EQ(sig, sig_square);

  EXPECT_NEAR(sig->signal->getIndex(0)->getData(), 1.44f, FLOAT_TOLERANCE);
  EXPECT_NEAR(sig->signal->getIndex(1)->getData(), 4.41f, FLOAT_TOLERANCE);
  EXPECT_NEAR(sig->signal->getIndex(2)->getData(), 1.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(sig->signal->getIndex(3)->getData(), 4.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(sig->signal->getIndex(4)->getData(), 9.0f, FLOAT_TOLERANCE);

  EXPECT_EQ(sig->signal->getIndex(4)->getNext(), nullptr);

  delete sig;
}
