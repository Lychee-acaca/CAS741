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
#include <math.h>

#include <fstream>
#include <string>

#include "src/dataStructure.hpp"
#include "test/unitTest/general.hpp"

static int readTestFile(const std::string &filename, DoublyLL<float> *b,
                        DoublyLL<float> *a, Signal *sig, Signal *y) {
  std::ifstream infile(filename);

  if (!infile) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return 1;
  }

  if (General::readSeqData(infile, b)) {
    return 1;
  }
  if (General::readSeqData(infile, a)) {
    return 1;
  }
  if (General::readSeqData(infile, sig->signal)) {
    return 1;
  }
  if (General::readSeqData(infile, y->signal)) {
    return 1;
  }

  return 0;
}

static void LfilterTest(const std::string &filename) {
  DoublyLL<float> *b = new DoublyLL<float>();
  DoublyLL<float> *a = new DoublyLL<float>();
  Signal *sig = new Signal(1);
  Signal *y = new Signal(1);
  EXPECT_EQ(readTestFile(filename, b, a, sig, y), 0);

  GeneralDigitalFilter *gdf = new GeneralDigitalFilter(b, a);

  Signal *y_hat = gdf->lfilter(sig);

  EXPECT_LE(General::RMSE(y->signal, y_hat->signal), 1e-5);

  delete b;
  delete a;
  delete sig;
  delete y;
  delete gdf;
  delete y_hat;
}

TEST(GDF_Test, RegularizeTest1) {
  DoublyLL<float> *b = new DoublyLL<float>();
  DoublyLL<float> *a = new DoublyLL<float>();
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
  DoublyLL<float> *b = new DoublyLL<float>();
  DoublyLL<float> *a = new DoublyLL<float>();
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

class LfilterTestSuite : public ::testing::TestWithParam<std::string> {};

TEST_P(LfilterTestSuite, RunsLfilterOnFile) {
  std::string file = GetParam();
  LfilterTest(file);
}

static std::vector<std::string> generateFilePaths() {
  std::vector<std::string> paths;
  for (int i = 1; i <= 20; ++i) {
    paths.push_back("../test/unitTest/data/lfilter" + std::to_string(i) +
                    ".txt");
  }
  return paths;
}

INSTANTIATE_TEST_SUITE_P(GDF_Test, LfilterTestSuite,
                         ::testing::ValuesIn(generateFilePaths()));
