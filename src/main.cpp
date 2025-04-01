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
#include "src/generalDigitalFilter.hpp"
#include "src/io_processing.hpp"
#include "src/logger.hpp"
#include "src/mmath.hpp"

Signal *LPF(Signal *sig) {
  DoublyLL *b = new DoublyLL();
  DoublyLL *a = new DoublyLL();

  b->push_back(6.68607912e-05);
  b->push_back(2.67443165e-04);
  b->push_back(4.01164747e-04);
  b->push_back(2.67443165e-04);
  b->push_back(6.68607912e-05);

  a->push_back(1.0f);
  a->push_back(-3.49868423f);
  a->push_back(4.61791585f);
  a->push_back(-2.72312355f);
  a->push_back(0.60496169f);

  GeneralDigitalFilter *gdf = new GeneralDigitalFilter(b, a);
  auto out = gdf->lfilter(sig);

  delete gdf;
  delete b;
  delete a;

  return out;
}

Signal *HPF(Signal *sig) {
  DoublyLL *b = new DoublyLL();
  DoublyLL *a = new DoublyLL();

  b->push_back(0.89220304f);
  b->push_back(-3.56881217f);
  b->push_back(5.35321825f);
  b->push_back(-3.56881217f);
  b->push_back(0.89220304f);

  a->push_back(1.0f);
  a->push_back(-3.77199675f);
  a->push_back(5.341624f);
  a->push_back(-3.36560165f);
  a->push_back(0.79602627f);

  GeneralDigitalFilter *gdf = new GeneralDigitalFilter(b, a);
  auto out = gdf->lfilter(sig);

  delete gdf;
  delete b;
  delete a;

  return out;
}

int main() {
  Logger::getInstance()->log("Hello", Logger::LogLevel::HIGH);
  Signal *sig = IO_Processing::readFromFile("../../../data/100.txt");
  Signal *sig_LPF = LPF(sig);
  IO_Processing::writeToFile("../../../data/output/100_LPF.txt", sig_LPF);
  Signal *sig_HPF = HPF(sig_LPF);
  IO_Processing::writeToFile("../../../data/output/100_HPF.txt", sig_HPF);

  return 0;
}
