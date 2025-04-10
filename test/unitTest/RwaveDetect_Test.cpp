/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/RwaveDetect.hpp"

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>

TEST(RwaveDetect_Test, detect) {
  std::string output_dir = "../test/unitTest/data/mitbih_100.output.txt";
  float RMSE = RwaveDetect::detect("../test/unitTest/data/mitbih_100.txt",
                                   "../test/unitTest/data/mitbih_100.ann.txt",
                                   output_dir);

  std::ifstream file(output_dir);
  if (!file) {
    std::cerr << "Error opening file" << std::endl;
  }
  std::string line;
  int lineCount = 0;
  while (std::getline(file, line)) {
    lineCount++;
  }
  file.close();
  if (remove(output_dir.c_str()) != 0) {
    std::cerr << "Error deleting file." << std::endl;
  }

  EXPECT_LE(RMSE, 1.0f);
  EXPECT_GE(lineCount, 2000);
}
