/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include <iostream>
#include <string>

#include "src/annRMSE.hpp"
#include "src/dataStructure.hpp"
#include "src/io_processing.hpp"
#include "src/logger.hpp"
#include "src/pantomp.hpp"

int main() {
  Logger::getInstance()->setLogLevel(Logger::LogLevel::LOW);
  Logger::getInstance()->log("Hello", Logger::LogLevel::HIGH);

  std::string id = "101";

  Signal *sig = IO_Processing::readFromFile("../../../data/" + id + ".txt");
  DoublyLL<int> *ann =
      IO_Processing::readAnnFromFile("../../../data/" + id + ".ann.txt");

  PanTompSolver ps;
  auto finalPeaks = ps.findPeak(sig);

  annRMSE_Solver as;
  float RMSE = as.calRMSE(finalPeaks, ann);
  Logger::getInstance()->log("RMSE = " + std::to_string(RMSE));

  IO_Processing::writeToFile("../../../data/output/" + id + "_fpeaks.txt",
                             finalPeaks);

  return 0;
}
