/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/RwaveDetect.hpp"

#include <string>

#include "src/annRMSE.hpp"
#include "src/dataStructure.hpp"
#include "src/io_processing.hpp"
#include "src/logger.hpp"
#include "src/pantomp.hpp"

float RwaveDetect::detect(std::string sig_path, std::string ann_path,
                          std::string output_path) {
  Signal* sig = IO_Processing::readFromFile(sig_path);

  PanTompSolver ps;
  DoublyLL<int>* finalPeaks = ps.findPeak(sig);

  annRMSE_Solver as;
  float RMSE = 0;
  if (ann_path != "") {
    DoublyLL<int>* ann = IO_Processing::readAnnFromFile(ann_path);
    RMSE = as.calRMSE(finalPeaks, ann);
    Logger::getInstance()->log("RMSE = " + std::to_string(RMSE));
    delete ann;
  }

  IO_Processing::writeToFile(output_path, finalPeaks);

  delete sig;
  delete finalPeaks;
  return RMSE;
}
