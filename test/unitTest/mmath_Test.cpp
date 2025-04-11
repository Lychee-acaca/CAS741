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

static int readTestFile(const std::string &filename, Signal *x, Signal *y) {
  std::ifstream infile(filename);

  if (!infile) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return 1;
  }

  if (General::readSeqData(infile, x->signal)) {
    return 1;
  }
  if (General::readSeqData(infile, y->signal)) {
    return 1;
  }

  return 0;
}

static void squareTest(const std::string &filename, bool inplace = false) {
  Signal *x = new Signal(1);
  Signal *y = new Signal(1);
  EXPECT_EQ(readTestFile(filename, x, y), 0);

  Signal *y_hat = MathFunc::calSquare(x, inplace);

  EXPECT_LE(General::RMSE(y->signal, y_hat->signal), 1e-5);

  delete x;
  delete y;
  if (!inplace) {
    delete y_hat;
  }
}

class calSquareSuite
    : public ::testing::TestWithParam<std::tuple<std::string, bool>> {};

TEST_P(calSquareSuite, RunsLfilterOnFile) {
  auto [file, inplace] = GetParam();
  squareTest(file, inplace);
}

static std::vector<std::tuple<std::string, bool>> generateFilePaths() {
  std::vector<std::tuple<std::string, bool>> paths;
  for (int i = 1; i <= 20; ++i) {
    std::string filepath =
        "../test/unitTest/data/square" + std::to_string(i) + ".txt";
    paths.emplace_back(filepath, false);
    paths.emplace_back(filepath, true);
  }
  return paths;
}

INSTANTIATE_TEST_SUITE_P(Math_Test, calSquareSuite,
                         ::testing::ValuesIn(generateFilePaths()));
