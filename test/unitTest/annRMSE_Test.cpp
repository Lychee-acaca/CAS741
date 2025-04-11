/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/annRMSE.hpp"

#include <gtest/gtest.h>

#include "src/dataStructure.hpp"
#include "test/unitTest/general.hpp"

static int readTestFile(const std::string &filename, int *tolerance,
                        float *RMSE, DoublyLL<int> *fp, DoublyLL<int> *ann) {
  std::ifstream infile(filename);

  if (!infile) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return 1;
  }

  if (!(infile >> (*tolerance))) {
    std::cerr << "Failed to read the tolerance." << std::endl;
    return 1;
  }

  if (!(infile >> (*RMSE))) {
    std::cerr << "Failed to read the RMSE." << std::endl;
    return 1;
  }

  if (General::readSeqData(infile, fp)) {
    return 1;
  }
  if (General::readSeqData(infile, ann)) {
    return 1;
  }

  return 0;
}

static void RMSE_Test(const std::string &filename) {
  int tolerance = 0;
  float RMSE = 0;
  DoublyLL<int> *fp = new DoublyLL<int>();
  DoublyLL<int> *ann = new DoublyLL<int>();
  EXPECT_EQ(readTestFile(filename, &tolerance, &RMSE, fp, ann), 0);

  annRMSE_Solver *as = new annRMSE_Solver(tolerance);
  float RMSE_hat = as->calRMSE(fp, ann);

  EXPECT_LE(fabs(RMSE_hat - RMSE), 1e-5);

  delete fp;
  delete ann;
  delete as;
}

class calRMSESuite : public ::testing::TestWithParam<std::string> {};

TEST_P(calRMSESuite, RunsLfilterOnFile) {
  std::string file = GetParam();
  RMSE_Test(file);
}

static std::vector<std::string> generateFilePaths() {
  std::vector<std::string> paths;
  for (int i = 1; i <= 20; ++i) {
    paths.push_back("../test/unitTest/data/RMSE" + std::to_string(i) + ".txt");
  }
  return paths;
}

INSTANTIATE_TEST_SUITE_P(RMSE_Test, calRMSESuite,
                         ::testing::ValuesIn(generateFilePaths()));
