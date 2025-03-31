/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include <gtest/gtest.h>

#include "src/dataStructure.hpp"

TEST(DoublyLL_Test, BasicAssertions) {
  DoublyLL *d1 = new DoublyLL();
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

  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  delete d1;
}
