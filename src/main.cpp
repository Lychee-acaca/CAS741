/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include <iostream>

#include "src/dataStructure.hpp"
#include "src/io_processing.hpp"
#include "src/logger.hpp"
#include "src/pantomp.hpp"

int main() {
  Logger::getInstance()->setLogLevel(Logger::LogLevel::LOW);
  Logger::getInstance()->log("Hello", Logger::LogLevel::HIGH);
  Signal *sig = IO_Processing::readFromFile("../../../data/100.txt");

  PanTompSolver ps;
  auto finalPeaks = ps.findPeak(sig);

  IO_Processing::writeToFile("../../../data/output/100_fpeaks.txt", finalPeaks);

  return 0;
}
