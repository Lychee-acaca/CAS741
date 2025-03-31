/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/generalDigitalFilter.hpp"

#include <gtest/gtest.h>

#include "src/dataStructure.hpp"
#include "test/unitTest/general.hpp"

TEST(GDF_Test, RegularizeTest1) {
  DoublyLL *b = new DoublyLL();
  DoublyLL *a = new DoublyLL();
  b->push_back(2.0f);
  b->push_back(3.0f);
  b->push_back(4.0f);
  b->push_back(5.0f);

  a->push_back(6.0f);
  a->push_back(7.0f);
  a->push_back(8.0f);
  GeneralDigitalFilter *gdf = new GeneralDigitalFilter(b, a);
  EXPECT_NEAR(b->getIndex(0)->getData(), 2.0f / 6.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(b->getIndex(1)->getData(), 3.0f / 6.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(b->getIndex(2)->getData(), 4.0f / 6.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(b->getIndex(3)->getData(), 5.0f / 6.0f, FLOAT_TOLERANCE);

  EXPECT_NEAR(a->getIndex(0)->getData(), 1.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(a->getIndex(1)->getData(), 7.0f / 6.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(a->getIndex(2)->getData(), 8.0f / 6.0f, FLOAT_TOLERANCE);
  delete gdf;
  delete b;
  delete a;
}

TEST(GDF_Test, RegularizeTest2) {
  GeneralDigitalFilter *gdf = new GeneralDigitalFilter();
  DoublyLL *b = new DoublyLL();
  DoublyLL *a = new DoublyLL();
  b->push_back(5.3f);
  b->push_back(4.2f);
  b->push_back(3.7f);
  b->push_back(8.6f);

  a->push_back(8.2f);
  a->push_back(8.3f);
  a->push_back(6.4f);
  a->push_back(7.5f);
  a->push_back(8.6f);
  gdf->setParam(b, a);

  EXPECT_NEAR(b->getIndex(0)->getData(), 5.3f / 8.2f, FLOAT_TOLERANCE);
  EXPECT_NEAR(b->getIndex(1)->getData(), 4.2f / 8.2f, FLOAT_TOLERANCE);
  EXPECT_NEAR(b->getIndex(2)->getData(), 3.7f / 8.2f, FLOAT_TOLERANCE);
  EXPECT_NEAR(b->getIndex(3)->getData(), 8.6f / 8.2f, FLOAT_TOLERANCE);

  EXPECT_NEAR(a->getIndex(0)->getData(), 1.0f, FLOAT_TOLERANCE);
  EXPECT_NEAR(a->getIndex(1)->getData(), 8.3f / 8.2f, FLOAT_TOLERANCE);
  EXPECT_NEAR(a->getIndex(2)->getData(), 6.4f / 8.2f, FLOAT_TOLERANCE);
  EXPECT_NEAR(a->getIndex(3)->getData(), 7.5f / 8.2f, FLOAT_TOLERANCE);
  EXPECT_NEAR(a->getIndex(4)->getData(), 8.6f / 8.2f, FLOAT_TOLERANCE);
  delete gdf;
  delete b;
  delete a;
}
