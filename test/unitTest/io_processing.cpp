/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/io_processing.hpp"

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>

#include "src/dataStructure.hpp"
#include "test/unitTest/general.hpp"

TEST(IO_Processing_Test, readAnnFromFile_noFile) {
  DoublyLL<int> *ann;
  ann = IO_Processing::readAnnFromFile("../test/unitTest/data/nofile");
  EXPECT_EQ(ann, nullptr);
}

TEST(IO_Processing_Test, readFromFile_noFile) {
  Signal *sig;
  sig = IO_Processing::readFromFile("../test/unitTest/data/nofile");
  EXPECT_EQ(sig, nullptr);
}

TEST(IO_Processing_Test, readAndWriteSignal) {
  Signal *sig;
  sig = IO_Processing::readFromFile("../test/unitTest/data/mitbih_100.txt");
  EXPECT_EQ(sig->fs, 360);
  EXPECT_EQ(sig->signal->getLen(), 650000);
  EXPECT_NEAR(sig->signal->getIndex(2)->getData(), -0.145000f, FLOAT_TOLERANCE);

  sig->fs = 500;
  sig->signal->getIndex(2)->setData(2.0f);

  IO_Processing::writeToFile("../test/unitTest/data/mitbih_100_test.txt", sig);
  delete sig;

  std::string output_path = "../test/unitTest/data/mitbih_100_test.txt";
  sig = IO_Processing::readFromFile(output_path);

  EXPECT_EQ(sig->fs, 500);
  EXPECT_EQ(sig->signal->getLen(), 650000);
  EXPECT_NEAR(sig->signal->getIndex(2)->getData(), 2.0f, FLOAT_TOLERANCE);

  delete sig;

  if (remove(output_path.c_str()) != 0) {
    std::cerr << "Error deleting file." << std::endl;
  }
}

TEST(IO_Processing_Test, readAndWriteAnn) {
  DoublyLL<int> *ann;
  ann = IO_Processing::readAnnFromFile(
      "../test/unitTest/data/mitbih_100.ann.txt");
  EXPECT_EQ(ann->getLen(), 2239);
  EXPECT_EQ(ann->getIndex(3)->getData(), 946);

  ann->push_head(123);

  IO_Processing::writeToFile("../test/unitTest/data/mitbih_100_test.ann.txt",
                             ann);
  delete ann;

  std::string output_path = "../test/unitTest/data/mitbih_100_test.ann.txt";
  ann = IO_Processing::readAnnFromFile(output_path);

  EXPECT_EQ(ann->getLen(), 2240);
  EXPECT_EQ(ann->getIndex(0)->getData(), 123);
  EXPECT_EQ(ann->getIndex(4)->getData(), 946);

  delete ann;

  if (remove(output_path.c_str()) != 0) {
    std::cerr << "Error deleting file." << std::endl;
  }
}
