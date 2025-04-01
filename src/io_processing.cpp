/*
 * Copyright (c) 2025 Junwei Lin
 * All rights reserved.
 *
 * Licensed under the MIT License. You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/MIT
 */

#include "src/io_processing.hpp"

#include <fstream>
#include <iostream>
#include <string>

Signal *IO_Processing::readFromFile(std::string filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cerr << "unable to open the file " << filename << std::endl;
    return nullptr;
  }

  Signal *sig = new Signal();
  std::string line;
  if (!std::getline(file, line)) {
    file.close();
    return nullptr;
  }
  sig->fs = std::stoi(line);

  while (std::getline(file, line)) {
    float f_num = std::stof(line);
    sig->signal->push_back(f_num);
  }

  file.close();
  return sig;
}

void IO_Processing::writeToFile(std::string filename, Signal *x) {
  std::ofstream file(filename);

  if (!file) {
    std::cerr << "unable to open the file " << filename << std::endl;
    return;
  }

  file << x->fs << std::endl;

  for (auto it = x->signal->begin(); it != x->signal->end(); ++it) {
    file << (*it) << std::endl;
  }

  file.close();
  return;
}
