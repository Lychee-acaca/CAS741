/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/dataStructure.hpp"

#include <gtest/gtest.h>

#include "test/unitTest/general.hpp"

TEST(DoublyLL_Test, BasicOperations) {
  DoublyLL<float> *d1 = new DoublyLL<float>();
  d1->push_back(1.23f);
  d1->push_back(2.23f);
  d1->push_back(3.23f);
  d1->push_back(4.23f);
  d1->push_back(5.23f);
  d1->push_back(6.23f);
  d1->push_back(7.23f);
  d1->push_back(8.23f);
  d1->push_back(9.23f);

  d1->insert(0, 114.0f);
  d1->insert(1, 115.0f);

  d1->pop_head();
  d1->remove(3);

  EXPECT_NEAR(d1->getIndex(0)->getData(), 115.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(1)->getData(), 1.23f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(2)->getData(), 2.23f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(3)->getData(), 4.23f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(4)->getData(), 5.23f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(5)->getData(), 6.23f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(6)->getData(), 7.23f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(7)->getData(), 8.23f, FLOAT_TOLERANCE);
  EXPECT_NEAR(d1->getIndex(8)->getData(), 9.23f, FLOAT_TOLERANCE);

  EXPECT_EQ(d1->getIndex(8)->getNext(), nullptr);
  EXPECT_EQ(d1->getLen(), 9);
  delete d1;
}
